// -------------------------------------------------------------------------
//    @FileName         ��    AFCMasterModule.h
//    @Author           ��    Ark Game Tech
//    @Date             ��    2012-12-15
//    @Module           ��    AFCMasterModule
//
// -------------------------------------------------------------------------

#ifndef AFC_MASTER_MODULE_H
#define AFC_MASTER_MODULE_H

#include "SDK/Interface/AFIKernelModule.h"
#include "SDK/Interface/AFIMasterModule.h"
#include "SDK/Interface/AFIMasterNet_ServerModule.h"

class AFCMasterModule
    : public AFIMasterModule
{

public:
    AFCMasterModule(AFIPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();
protected:


private:

    AFIKernelModule* m_pKernelModule;
};

#endif