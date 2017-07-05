// -------------------------------------------------------------------------
//    @FileName         ��    AFIGameServerToWorldModule.h
//    @Author           ��    Ark Game Tech
//    @Date             ��    2012-12-15
//    @Module           ��    AFIGameServerToWorldModule
//
// -------------------------------------------------------------------------

#ifndef AFI_GAMESERVERTOWORLDMODULE_H
#define AFI_GAMESERVERTOWORLDMODULE_H

#include <iostream>
#include "AFIModule.h"
#include "AFINetClientModule.hpp"

class AFIGameServerToWorldModule
    : public AFIModule
{

public:
	virtual void SendBySuit(const int& nHashKey, const int nMsgID, const char* msg, const uint32_t nLen) = 0;
    virtual AFINetClientModule* GetClusterClientModule() = 0;
};

#endif