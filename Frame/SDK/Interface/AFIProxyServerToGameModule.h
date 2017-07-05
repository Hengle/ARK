// -------------------------------------------------------------------------
//    @FileName         ��    AFIProxyServerToGameModule.h
//    @Author           ��    Ark Game Tech
//    @Date             ��    2012-12-15
//    @Module           ��    AFIProxyServerToGameModule
//
// -------------------------------------------------------------------------

#ifndef AFI_PROXYNET_TO_GAME_H
#define AFI_PROXYNET_TO_GAME_H

#include <iostream>
#include "AFIModule.h"
#include "AFINetClientModule.hpp"

class AFIProxyServerToGameModule
    : public  AFIModule
{
public:
	virtual AFINetClientModule* GetClusterModule() = 0;
};

#endif