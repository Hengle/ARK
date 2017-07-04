// -------------------------------------------------------------------------
//    @FileName			:    NFCWorldNet_ServerModule.h
//    @Author           :    Ark Game Tech
//    @Date             :    2013-01-02
//    @Module           :    NFCWorldNet_ServerModule
//    @Desc             :
// -------------------------------------------------------------------------

#ifndef NFC_WORLDNET_SERVER_MODULE_H
#define NFC_WORLDNET_SERVER_MODULE_H

//  the cause of sock'libariy, thenfore "NFCNet.h" much be included first.
#include "SDK/Core/NFMap.h"
#include "NFComm/NFMessageDefine/NFMsgDefine.h"
#include "SDK/Interface/NFIWorldToMasterModule.h"
#include "SDK/Interface/NFIWorldLogicModule.h"
#include "SDK/Interface/NFINetModule.h"
#include "SDK/Interface/NFIClassModule.h"
#include "SDK/Interface/NFIElementModule.h"
#include "SDK/Interface/NFILogModule.h"
#include "SDK/Interface/NFIWorldNet_ServerModule.h"
#include "SDK/Interface/NFIKernelModule.h"
#include "SDK/Interface/NFILoginNet_ServerModule.h"

class NFCWorldNet_ServerModule
    : public NFIWorldNet_ServerModule
{
public:
    NFCWorldNet_ServerModule(NFIPluginManager* p)
    {
        pPluginManager = p;
        mnLastCheckTime = pPluginManager->GetNowTime();
    }

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();

    virtual bool AfterInit();

    virtual void LogReceive(const char* str) {}
    virtual void LogSend(const char* str) {}

    virtual bool SendMsgToGame(const int nGameID, const NFMsg::EGameMsgID eMsgID, google::protobuf::Message& xData, const AFGUID nPlayer = AFGUID());
    virtual bool SendMsgToGame(const AFDataList& argObjectVar, const AFDataList& argGameID,  const NFMsg::EGameMsgID eMsgID, google::protobuf::Message& xData);
    virtual bool SendMsgToPlayer(const NFMsg::EGameMsgID eMsgID, google::protobuf::Message& xData, const AFGUID nPlayer);

    virtual int OnObjectListEnter(const AFDataList& self, const AFDataList& argVar);
    virtual int OnObjectListLeave(const AFDataList& self, const AFDataList& argVar);
    virtual int OnPropertyEnter(const AFDataList& argVar, const AFDataList& argGameID, const AFGUID& self);
    virtual int OnRecordEnter(const AFDataList& argVar, const AFDataList& argGameID, const AFGUID& self);
    virtual bool OnRecordEnterPack(NF_SHARE_PTR<NFIRecord> pRecord, NFMsg::ObjectRecordBase* pObjectRecordBase);

    virtual NF_SHARE_PTR<ServerData> GetSuitProxyForEnter();
	virtual NFINetModule* GetNetModule();

    virtual int GetPlayerGameID(const AFGUID self);

protected:

    void OnSocketEvent(const int nSockIndex, const NF_NET_EVENT eEvent, const AFGUID& xClientID, const int nServerID);

    //���Ӷ�ʧ,ɾ2��(���Ӷ����ʺŶ���)
    void OnClientDisconnect(const int nAddress);
    //������
    void OnClientConnected(const int nAddress);



protected:

    void OnGameServerRegisteredProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);
    void OnGameServerUnRegisteredProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);
    void OnRefreshGameServerInfoProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);

    void OnProxyServerRegisteredProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);
    void OnProxyServerUnRegisteredProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);
    void OnRefreshProxyServerInfoProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);

    int OnLeaveGameProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);
    //////////////////////////////////////////////////////////////////////////

    void SynGameToProxy();
    void SynGameToProxy(const int nFD);

    //////////////////////////////////////////////////////////////////////////
    void LogGameServer();

protected:

    void OnOnlineProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);
    void OnOfflineProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);


private:

    NFINT64 mnLastCheckTime;

    //serverid,data
    NFMapEx<int, ServerData> mGameMap;
    NFMapEx<int, ServerData> mProxyMap;

    NFIElementModule* m_pElementModule;
    NFIClassModule* m_pClassModule;
    NFIWorldLogicModule* m_pWorldLogicModule;
    NFIKernelModule* m_pKernelModule;
    NFILogModule* m_pLogModule;
	NFINetModule* m_pNetModule;

};

#endif
