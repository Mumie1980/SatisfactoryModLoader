// This file has been automatically generated by the Unreal Header Implementation tool

#include "Replication/FGStaticReplicatedActor.h"

AFGStaticReplicatedActor::AFGStaticReplicatedActor() : Super() {
	this->PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.bTickEvenWhenPaused = false;
	this->PrimaryActorTick.bCanEverTick = false;
	this->PrimaryActorTick.bStartWithTickEnabled = false;
	this->PrimaryActorTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryActorTick.TickInterval = 0.0;
	this->bReplicates = true;
	this->NetDormancy = ENetDormancy::DORM_DormantAll;
}
