#include "AlpakitModEntryList.h"
#include "Alpakit.h"
#include "AlpakitModEntry.h"
#include "Interfaces/IPluginManager.h"
#include "Slate.h"

#define LOCTEXT_NAMESPACE "AlpakitModListEntry"

void SAlpakitModEntryList::Construct(const FArguments& Args) {
    ChildSlot[
        SNew(SVerticalBox)
        + SVerticalBox::Slot().AutoHeight()[
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot().AutoWidth()[
                SNew(SButton)
                .Text(LOCTEXT("PackageModAlpakitAll", "Alpakit Selected!"))
                .OnClicked(this,& SAlpakitModEntryList::PackageAllMods)
                .IsEnabled(this, &SAlpakitModEntryList::IsPackageButtonEnabled)
            ]
            + SHorizontalBox::Slot().AutoWidth()[
                SNew(SButton)
                .Text(LOCTEXT("PackageModCheckAll", "Check All"))
                .OnClicked(this,& SAlpakitModEntryList::CheckAllMods)
            ]
            + SHorizontalBox::Slot().AutoWidth()[
                SNew(SButton)
                .Text(LOCTEXT("PackageModUncheckAll", "Check None"))
                .OnClicked(this,& SAlpakitModEntryList::UncheckAllMods)
            ]
            + SHorizontalBox::Slot().FillWidth(1.0f)
            + SHorizontalBox::Slot().AutoWidth()[
                SNew(SButton)
                .Text(LOCTEXT("CreateMod", "Create Mod"))
                .OnClicked(this,& SAlpakitModEntryList::CreateMod)
            ]
        ]
        + SVerticalBox::Slot().FillHeight(1.0f)[
            SNew(SScrollBox)
            .Orientation(Orient_Vertical)
            .ScrollBarAlwaysVisible(true)
            + SScrollBox::Slot()[
                SAssignNew(ModList, SListView<TSharedRef<IPlugin>>)
                .SelectionMode(ESelectionMode::None)
                .ListItemsSource(&FilteredMods)
                .OnGenerateRow_Lambda(
                    [this](TSharedRef<IPlugin> Mod, const TSharedRef<STableViewBase>& List) {
                        return SNew(STableRow<TSharedRef<IPlugin>>, List)[
                            SNew(SAlpakitModEntry, Mod, SharedThis(this))
                        ];
                    })
            ]
        ]
    ];

    LoadMods();
    IPluginManager::Get().OnNewPluginCreated().AddSP(this, &SAlpakitModEntryList::OnNewPluginCreated);
}

bool DoesPluginHaveRuntime(const IPlugin& Plugin) {
    //Content plugins always have runtime component
    if (Plugin.GetDescriptor().bCanContainContent) {
        return true;
    }
    //C++ plugins have runtime component as long as one of their modules does
    for (const FModuleDescriptor& Module : Plugin.GetDescriptor().Modules) {
        if (Module.Type == EHostType::Runtime ||
            Module.Type == EHostType::RuntimeNoCommandlet ||
            Module.Type == EHostType::RuntimeAndProgram ||
            Module.Type == EHostType::ClientOnly ||
            Module.Type == EHostType::ClientOnlyNoCommandlet ||
            Module.Type == EHostType::ServerOnly ||
            Module.Type == EHostType::CookedOnly) {
            return true;
        }
    }
    return false;
}

void SAlpakitModEntryList::LoadMods() {
    Mods.Empty();
    const TArray<TSharedRef<IPlugin>> EnabledPlugins = IPluginManager::Get().GetEnabledPlugins();
    for (TSharedRef<IPlugin> Plugin : EnabledPlugins) {
        //Skip SMLEditor, editor-only plugin
        if (Plugin->GetName() == TEXT("SMLEditor")) {
            continue;
        }
        //Only include project plugins for now
        //TODO make sure UAT task supports engine plugins
        if ((bShowEngine && Plugin->GetType() == EPluginType::Engine) ||
            (bShowProject && Plugin->GetType() == EPluginType::Project) ||
            Plugin->GetType() == EPluginType::Mod) {
            
            const bool bHasRuntime = DoesPluginHaveRuntime(Plugin.Get());
            if (bHasRuntime) {
                Mods.Add(Plugin);
            }
        }
    }
    Mods.Sort([](const TSharedRef<IPlugin> Plugin1, const TSharedRef<IPlugin> Plugin2) {
        return Plugin1->GetName() < Plugin2->GetName();
    });
    Filter(LastFilter);
}

bool PluginMatchesSearchTokens(const IPlugin& Plugin, const TArray<FString>& Tokens) {
    const FString PluginName = Plugin.GetName();
    const FString FriendlyName = Plugin.GetDescriptor().FriendlyName;
    const FString Description = Plugin.GetDescriptor().Description;

    for (const FString& Token : Tokens) {
        if (PluginName.Contains(Token) ||
            FriendlyName.Contains(Token) ||
            Description.Contains(Token)) {
            return true;
        }
    }
    return false;
}

void SAlpakitModEntryList::Filter(const FString& InFilter) {
    LastFilter = InFilter;
    FilteredMods.Empty();

    if (InFilter.IsEmpty()) {
        FilteredMods = Mods;
    } else {
        // tokenize filter keywords
        TArray<FString> FilterTokens;
        InFilter.ParseIntoArray(FilterTokens, TEXT(" "), true);

        // check each mod for it to contain the tokens
        for (TSharedRef<IPlugin> Mod : Mods) {
            // check each token in mod name
            if (PluginMatchesSearchTokens(Mod.Get(), FilterTokens)) {
                FilteredMods.Add(Mod);
            }
        }
    }

    ModList->RequestListRefresh();
}

FString SAlpakitModEntryList::GetLastFilter() const {
    return LastFilter;
}

void SAlpakitModEntryList::SetShowEngine(bool bInShowEngine) {
    bShowEngine = bInShowEngine;
    LoadMods();
}

void SAlpakitModEntryList::SetShowProject(bool bInShowProject) {
    bShowProject = bInShowProject;
    LoadMods();
}

void SAlpakitModEntryList::OnNewPluginCreated(IPlugin& Plugin)
{
    LoadMods();
}

FReply SAlpakitModEntryList::PackageAllMods() {
    TArray<TSharedRef<IPlugin>> ModsToPackage;

    UE_LOG(LogAlpakit, Display, TEXT("Alpakit Selected!"));

    for (TSharedRef<IPlugin> Mod : FilteredMods) {
        UE_LOG(LogAlpakit, Display, TEXT("Collecting Plugin %s!"), *Mod->GetName());

        TSharedPtr<ITableRow> TableRow = ModList->WidgetFromItem(Mod);
        if (!TableRow.IsValid()) {
            UE_LOG(LogAlpakit, Display, TEXT("TableRow not found!"));
            continue;
        }

        TSharedPtr<SAlpakitModEntry> ModEntry = StaticCastSharedPtr<SAlpakitModEntry>(TableRow->GetContent());
        if (!ModEntry.IsValid()) {
            UE_LOG(LogAlpakit, Display, TEXT("TableRow content is not valid!"));
            continue;
        }

        if(!ModEntry->IsSelected()) {
            UE_LOG(LogAlpakit, Display, TEXT("Plugin is not selected: %s"), * Mod->GetName());
            continue;
        }

        ModsToPackage.Add(Mod);
    }

    if (ModsToPackage.Num() == 0) {
        return FReply::Handled();
    }

    FAlpakitModule::Get().PackageMods(ModsToPackage);
    
    return FReply::Handled();
}

FReply SAlpakitModEntryList::CheckAllMods() {
    for (TSharedRef<IPlugin> Mod : FilteredMods) {
        TSharedPtr<ITableRow> TableRow = ModList->WidgetFromItem(Mod);
        if (!TableRow.IsValid()) {
            UE_LOG(LogAlpakit, Display, TEXT("TableRow not found!"));
            continue;
        }

        TSharedPtr<SAlpakitModEntry> ModEntry = StaticCastSharedPtr<SAlpakitModEntry>(TableRow->GetContent());
        if (!ModEntry.IsValid()) {
            UE_LOG(LogAlpakit, Display, TEXT("TableRow content is not valid!"));
            continue;
        }
        ModEntry->SetSelected(true);
    }
    return FReply::Handled();
}


FReply SAlpakitModEntryList::UncheckAllMods() {
    for (TSharedRef<IPlugin> Mod : FilteredMods) {
        TSharedPtr<ITableRow> TableRow = ModList->WidgetFromItem(Mod);
        if (!TableRow.IsValid()) {
            UE_LOG(LogAlpakit, Display, TEXT("TableRow not found!"));
            continue;
        }

        TSharedPtr<SAlpakitModEntry> ModEntry = StaticCastSharedPtr<SAlpakitModEntry>(TableRow->GetContent());
        if (!ModEntry.IsValid()) {
            UE_LOG(LogAlpakit, Display, TEXT("TableRow content is not valid!"));
            continue;
        }
        ModEntry->SetSelected(false);
    }
    return FReply::Handled();
}

FReply SAlpakitModEntryList::CreateMod()
{
    FGlobalTabmanager::Get()->TryInvokeTab(FAlpakitModule::ModCreatorTabName);
    return FReply::Handled();
}

bool SAlpakitModEntryList::IsPackageButtonEnabled() const {
	return !FAlpakitModule::Get().IsPackaging();
}

#undef LOCTEXT_NAMESPACE
