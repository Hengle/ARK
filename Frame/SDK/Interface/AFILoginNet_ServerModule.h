// -------------------------------------------------------------------------
//    @FileName         ��    AFILoginNet_ServerModule.h
//    @Author           ��    Ark Game Tech
//    @Date             ��    2012-12-15
//    @Module           ��    AFILoginNet_ServerModule
//
// -------------------------------------------------------------------------

#ifndef AFI_LOGINNET_SERVERMODULE_H
#define AFI_LOGINNET_SERVERMODULE_H

#include <iostream>
#include "AFIModule.h"
#include "AFINetModule.h"

class AFILoginNet_ServerModule
    : public AFIModule
{
public:

    virtual int OnSelectWorldResultsProcess(const int nWorldID, const AFGUID xSenderID, const int nLoginID, const std::string& strAccount, const std::string& strWorldIP, const int nWorldPort, const std::string& strKey) = 0;

};

#endif