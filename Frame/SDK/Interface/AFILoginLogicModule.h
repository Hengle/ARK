// -------------------------------------------------------------------------
//    @FileName         ��    AFILoginNet_ServerModule.h
//    @Author           ��    Ark Game Tech
//    @Date             ��    2012-12-15
//    @Module           ��    AFILoginNet_ServerModule
//
// -------------------------------------------------------------------------

#ifndef AFI_LOGINLOGIC_MODULE_H
#define AFI_LOGINLOGIC_MODULE_H

#include <iostream>
#include "AFIModule.h"

class AFILoginLogicModule
    : public AFIModule
{
public:
    virtual int OnLoginProcess(const AFGUID& object, const std::string& strAccount, const std::string& strPwd) = 0;

};

#endif