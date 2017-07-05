// -------------------------------------------------------------------------
//    @FileName         ��    AFIGameServerConfigModule.h
//    @Author           ��    Ark Game Tech
//    @Date             ��    2013-04-16
//    @Module           ��    AFIGameServerConfigModule
//
// -------------------------------------------------------------------------

#ifndef AFI_GAMESERVER_COAFIG_MODULE_H
#define AFI_GAMESERVER_COAFIG_MODULE_H

#include <iostream>
#include "AFIModule.h"

class AFIGameServerConfigModule
    : public AFIModule
{
public:
    virtual bool AddSceneToActor(const int nSceneID, const int nGameServer) = 0;
    virtual int GetActorID(const int nSceneID) = 0;
};

#endif