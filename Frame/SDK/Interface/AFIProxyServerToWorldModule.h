// -------------------------------------------------------------------------
//    @FileName         ��    AFIProxyServerNet_ClientModule.h
//    @Author           ��    Ark Game Tech
//    @Date             ��    2012-12-15
//    @Module           ��    AFIProxyServerNet_ClientModule
//
// -------------------------------------------------------------------------

#ifndef AFI_PROXYNET_CLIENTMODULE_H
#define AFI_PROXYNET_CLIENTMODULE_H

#include <iostream>
#include "AFIModule.h"
#include "AFINetClientModule.hpp"

class AFIProxyServerToWorldModule
    : public  AFIModule
{
public:
	virtual AFINetClientModule* GetClusterModule() = 0;
    virtual bool VerifyConnectData(const std::string& strAccount, const std::string& strKey) = 0;
};

#endif