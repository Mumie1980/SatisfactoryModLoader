// This file has been automatically generated by the Unreal Header Implementation tool

#include "Security/SocketSSL.h"

FSocketSSL::FSocketSSL(FUniqueSocket&& InUnderlyingSocket,  ssl_ctx_st* InSslContext){ }
FSocketSSL::~FSocketSSL(){ }
bool FSocketSSL::InitializeSslState(bool bIsServerSocket){ return bool(); }
void FSocketSSL::SetVerifyPeer(bool bVerifyPeer){ }
bool FSocketSSL::Shutdown(ESocketShutdownMode Mode){ return bool(); }
bool FSocketSSL::Close(){ return bool(); }
bool FSocketSSL::Bind(const FInternetAddr& Addr){ return bool(); }
bool FSocketSSL::Connect(const FInternetAddr& Addr){ return bool(); }
bool FSocketSSL::Listen(int32 MaxBacklog){ return bool(); }
bool FSocketSSL::WaitForPendingConnection(bool& bHasPendingConnection, const FTimespan& WaitTime){ return bool(); }
bool FSocketSSL::HasPendingData(uint32& PendingDataSize){ return bool(); }
FSocket* FSocketSSL::Accept(const FString& SocketDescription1){ return nullptr; }
FSocket* FSocketSSL::Accept(FInternetAddr& OutAddr, const FString& SocketDescription1){ return nullptr; }
bool FSocketSSL::SendTo(const uint8* Data, int32 Count, int32& BytesSent, const FInternetAddr& Destination){ return bool(); }
bool FSocketSSL::Send(const uint8* Data, int32 Count, int32& BytesSent){ return bool(); }
bool FSocketSSL::RecvFrom(uint8* Data, int32 BufferSize, int32& BytesRead, FInternetAddr& Source, ESocketReceiveFlags::Type Flags){ return bool(); }
bool FSocketSSL::Recv(uint8* Data,int32 BufferSize,int32& BytesRead, ESocketReceiveFlags::Type Flags){ return bool(); }
bool FSocketSSL::Wait(ESocketWaitConditions::Type Condition, FTimespan WaitTime){ return bool(); }
ESocketConnectionState FSocketSSL::GetConnectionState(){ return ESocketConnectionState(); }
void FSocketSSL::GetAddress(FInternetAddr& OutAddr){ }
bool FSocketSSL::GetPeerAddress(FInternetAddr& OutAddr){ return bool(); }
bool FSocketSSL::SetNonBlocking(bool bIsNonBlocking){ return bool(); }
bool FSocketSSL::SetNoDelay(bool bIsNoDelay){ return bool(); }
bool FSocketSSL::SetBroadcast(bool bAllowBroadcast){ return bool(); }
bool FSocketSSL::JoinMulticastGroup(const FInternetAddr& GroupAddress){ return bool(); }
bool FSocketSSL::JoinMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress){ return bool(); }
bool FSocketSSL::LeaveMulticastGroup(const FInternetAddr& GroupAddress){ return bool(); }
bool FSocketSSL::LeaveMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress){ return bool(); }
bool FSocketSSL::SetMulticastLoopback(bool bLoopback){ return bool(); }
bool FSocketSSL::SetMulticastTtl(uint8 TimeToLive){ return bool(); }
bool FSocketSSL::SetMulticastInterface(const FInternetAddr& InterfaceAddress){ return bool(); }
bool FSocketSSL::SetReuseAddr(bool bAllowReuse){ return bool(); }
bool FSocketSSL::SetLinger(bool bShouldLinger , int32 Timeout){ return bool(); }
bool FSocketSSL::SetRecvErr(bool bUseErrorQueue){ return bool(); }
bool FSocketSSL::SetSendBufferSize(int32 Size,int32& NewSize){ return bool(); }
bool FSocketSSL::SetReceiveBufferSize(int32 Size,int32& NewSize){ return bool(); }
int32 FSocketSSL::GetPortNo(){ return int32(); }
bool FSocketSSL::SetIpPktInfo(bool bEnable){ return bool(); }
bool FSocketSSL::RecvFromWithPktInfo(uint8* Data, int32 BufferSize, int32& BytesRead, FInternetAddr& Source, FInternetAddr& Destination, ESocketReceiveFlags::Type Flags){ return bool(); }
int32 FSocketSSL::AttemptInitiateHandshake(){ return int32(); }
bool FSocketSSL::IsSSLOperationWaitingForData(int32 ResultCode) const{ return bool(); }
void FSocketSSL::NotifySSLCallError(int32 ResultCode){ }
void FSocketSSL::SetSSLConnectionState(ESSLConnectionState NewState){ }
void FSocketSSL::ShutdownSSLConnectionAndWait(const FTimespan& MaxWaitTime){ }
FSocket* FSocketSSL::AcceptInternal(FInternetAddr* OutAddr, const FString& InSocketDescription) const{ return nullptr; }
int32 FSocketSSL::StaticSslErrorHandler(const char* AnsiErrorStr, size_t StrLen, void* UserData){ return int32(); }
void FSocketSSL::StaticSslInfoHandler(const  ssl_st* InSslInstance, int32 InEventType, int32 InEventVal){ }
