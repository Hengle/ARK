// -------------------------------------------------------------------------
//    @FileName      :    AFCEventRouteModule.h.h
//    @Author           :    Ark Game Tech
//    @Date             :    2015-01-02
//    @Module           :    AFCEventRouteModule.h
//    @Desc         :   �¼�·�ɣ���Ҫ��������ֲ�ʽ����Щ�����ڱ�������Ȼ����Ҫת�����¼����ʼ���
// -------------------------------------------------------------------------

#ifndef _AFC_EVENTROUTE_MODULE_H_
#define _AFC_EVENTROUTE_MODULE_H_

#include "AFComm/NFPluginModule/AFIPluginManager.h"
#include "AFComm/NFPluginModule/AFIKernelModule.h"
#include "AFComm/NFPluginModule/AFIGameLogicModule.h"
#include "AFComm/NFPluginModule/AFIEventProcessModule.h"
#include "AFComm/NFPluginModule/AFIEventRouteModule.h"
#include "AFComm/NFPluginModule/AFILogModule.h"
#include "AFComm/NFPluginModule/AFIPropertyConfigModule.h"

class AFCEventRouteModule
    : public AFIEventRouteModule
{
public:
    AFCEventRouteModule(AFIPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual ~AFCEventRouteModule() {};

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute(const float fLasFrametime, const float fStartedTime);
    virtual bool AfterInit();

public:
    virtual bool StartRouteEvent(const AFIDENTID& self, const AFIDataList& xDataList);

    virtual bool ReceiveRouteEvent(const AFIDENTID& self, const AFIDataList& xDataList);

private:
    AFIEventProcessModule* m_pEventProcessModule;
    AFIKernelModule* m_pKernelModule;
    AFILogModule* m_pLogModule;

};


#endif
