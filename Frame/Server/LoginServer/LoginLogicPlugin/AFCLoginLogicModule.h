// -------------------------------------------------------------------------
//    @FileName			:    NFCLoginLogicModule.h
//    @Author           :    Ark Game Tech
//    @Date             :    2012-12-15
//    @Module           :    NFCLoginLogicModule
//
// -------------------------------------------------------------------------

#ifndef NFC_LOGINLOGIC_MODULE_H
#define NFC_LOGINLOGIC_MODULE_H

#include "SDK/Core/NFMap.h"
#include "SDK/Interface/NFIKernelModule.h"
#include "SDK/Interface/NFILoginLogicModule.h"
#include "SDK/Interface/NFILoginNet_ServerModule.h"

class NFCLoginLogicModule
    : public NFILoginLogicModule
{
public:
    NFCLoginLogicModule(NFIPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();

    virtual bool AfterInit();

    virtual int OnLoginProcess(const AFGUID& object, const std::string& strAccount, const std::string& strPwd);

protected:

protected:

    NFILoginNet_ServerModule* m_pLoginNet_ServerModule;
private:
};

#endif