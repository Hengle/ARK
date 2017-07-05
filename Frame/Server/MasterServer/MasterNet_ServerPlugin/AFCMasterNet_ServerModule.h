// -------------------------------------------------------------------------
//    @FileName			:    AFCMasterNet_ServerModule.h
//    @Author           :    Ark Game Tech
//    @Date             :    2013-01-02
//    @Module           :    AFCMasterNet_ServerModule
//    @Desc             :
// -------------------------------------------------------------------------

#ifndef AFC_MASTERNET_SERVER_MODULE_H
#define AFC_MASTERNET_SERVER_MODULE_H

//  the cause of sock'libariy, thenfore "AFCNet.h" much be included first.

#include "SDK/Proto/NFMsgDefine.h"
#include "SDK/Interface/AFIMasterNet_ServerModule.h"
#include "SDK/Interface/AFIKernelModule.h"
#include "SDK/Interface/AFILogModule.h"
#include "SDK/Interface/AFINetModule.h"
#include "SDK/Interface/AFIClassModule.h"
#include "SDK/Interface/AFIElementModule.h"

class AFCMasterNet_ServerModule
    : public AFIMasterNet_ServerModule
{
public:
    AFCMasterNet_ServerModule(AFIPluginManager* p)
    {
		pPluginManager = p;
        mnLastLogTime = pPluginManager->GetNowTime();
    }

    virtual bool Init();
    virtual bool Shut();

    virtual bool AfterInit();
    virtual bool Execute();

    virtual void LogReceive(const char* str) {}
    virtual void LogSend(const char* str) {}

protected:

    void OnSocketEvent(const int nSockIndex, const NF_NET_EVENT eEvent, const AFGUID& xClientID, const int nServerID);

    //���Ӷ�ʧ,ɾ2��(���Ӷ����ʺŶ���)
    void OnClientDisconnect(const int nAddress);
    //������
    void OnClientConnected(const int nAddress);

protected:
    //���������ע�ᣬˢ����Ϣ
    void OnWorldRegisteredProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);
    void OnWorldUnRegisteredProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);
    void OnRefreshWorldInfoProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);

    //////////////////////////////////////////////////////////////////////////
    //��¼������ע�ᣬˢ����Ϣ
    void OnLoginRegisteredProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);
    void OnLoginUnRegisteredProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);
    void OnRefreshLoginInfoProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);

    //ѡ�������������Ϣ
    void OnSelectWorldProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);
    void OnSelectServerResultProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);

    //////////////////////////////////////////////////////////////////////////

    void SynWorldToLogin();
    void LogGameServer();

	void OnHeartBeat(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);
	void InvalidMessage(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen, const AFGUID& xClientID);

private:

    AFINT64 mnLastLogTime;

    //serverid,data
    AFMapEx<int, ServerData> mWorldMap;
    AFMapEx<int, ServerData> mLoginMap;


    AFIElementModule* m_pElementModule;
    AFIClassModule* m_pClassModule;
    AFIKernelModule* m_pKernelModule;
    AFILogModule* m_pLogModule;
	AFINetModule* m_pNetModule;
};

#endif