/*
* This source file is part of ArkGameFrame
* For the latest info, see https://github.com/ArkGame
*
* Copyright (c) 2013-2018 ArkGame authors.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#pragma once

#include "SDK/Interface/AFIKernelModule.h"
#include "SDK/Interface/AFIElementModule.h"
#include "SDK/Interface/AFIPluginManager.h"
#include "SDK/Interface/AFILogModule.h"

class Example3Module : public AFIModule
{
public:
    Example3Module(AFIPluginManager* p): mLastTime(0)
        , m_pKernelModule(nullptr)
        , m_pElementModule(nullptr)
    {
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool PostInit();

    virtual bool Update();

    virtual bool PreShut();
    virtual bool Shut();

protected:
    int OnEvent(const AFGUID & self, const int event, const AFIDataList & arg);
    int OnClassCallBackEvent(const AFGUID & self, const std::string & strClassName, const ARK_ENTITY_EVENT event, const AFIDataList & arg);
    int OnIntDataNodeCB(const AFGUID & self, const std::string & strProperty, const AFIData & oldVarList, const AFIData & newVarList);
    int OnStrDataNodeCB(const AFGUID & self, const std::string & strProperty, const AFIData & oldVarList, const AFIData & newVarList);

    int OnFightHeroTableCB(const AFGUID& self, const DATA_TABLE_EVENT_DATA& table_data, const AFIData& old_data, const AFIData& new_data);
    int OnHeartBeat(const AFGUID& self, const std::string& strHeartBeat, const int64_t nTime, const int nCount);

protected:
    int64_t mLastTime;
protected:
    AFIKernelModule* m_pKernelModule;
    AFIElementModule* m_pElementModule;
    AFILogModule* m_pLogModule;
};