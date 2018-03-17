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

#include "AFPlatform.hpp"
#include "AFDefine.h"
#include "AFSingleton.hpp"
#include "AFTime.hpp"

enum AFTimerEnum
{
    TIMER_TYPE_COUNT_LIMIT  = 0,
    TIMER_TYPE_FOREVER      = 1,

    MAX_SLOT = 1000,
    SLOT_TIME = 1,
    WHEEL_TIME = MAX_SLOT * SLOT_TIME,
};

class AFTimerData
{
public:
    AFTimerData() {}

    std::string name{ "" };
    uint8_t type{ 0 };
    uint16_t count{ 0 };
    uint32_t interval{ 0 };
    uint32_t rotation{ 0 };
    uint16_t slot{ 0 };
    TIMER_FUNCTOR_PTR callback;

    //callback data
    AFGUID entity_id{ 0 };

    AFTimerData* prev;
    AFTimerData* next;
};

class AFTimerManager : public AFSingleton<AFTimerManager>
{
public:
    AFTimerManager()
    {
        mnNowSlot = 0;
        mnLastUpdateTime = 0;
        memset(mxSlots, 0x0, sizeof(mxSlots));
    }

    ~AFTimerManager()
    {

    }

    void Init()
    {
        mnNowSlot = 0;
        mnLastUpdateTime = AFCTimeBase::GetInstance().GetNowMillisecond();
    }

    void Update()
    {
        UpdateTimerReg();
        UpdateTimer();
    }

    void Shut()
    {
        for (auto iter : mxTimers)
        {
            for (auto it : iter.second)
            {
                ARK_DELETE(it.second);
            }
        }

        mxTimers.clear();
        memset(mxSlots, 0x0, sizeof(mxSlots));
    }

    bool AddForverTimer(const std::string& name, const AFGUID& entity_id, uint32_t interval_time, TIMER_FUNCTOR_PTR callback)
    {
        auto data = FindTimerData(name, entity_id);
        if (data == nullptr)
        {
            data = (AFTimerData*)ARK_ALLOC(sizeof(AFTimerData));
            memset(data, 0x0, sizeof(data));
            AddTimerData(name, entity_id, data);
        }
        else
        {
            RemoveSlotTimer(data);
        }

        data->name = name;
        data->type = TIMER_TYPE_FOREVER;
        data->interval = interval_time;
        data->callback = callback;
        data->entity_id = entity_id;
        mxRegTimers.push_back(data);
        return true;
    }

    bool AddSingleTimer(const std::string& name, const AFGUID& entity_id, uint32_t interval_time, uint16_t count, TIMER_FUNCTOR_PTR callback)
    {
        auto data = FindTimerData(name, entity_id);
        if (data == nullptr)
        {
            data = (AFTimerData*)ARK_ALLOC(sizeof(AFTimerData));
            memset(data, 0x0, sizeof(data));
            AddTimerData(name, entity_id, data);
        }
        else
        {
            RemoveSlotTimer(data);
        }

        data->name = name;
        data->type = TIMER_TYPE_FOREVER;
        data->count = std::max((uint16_t)1, count);
        data->interval = interval_time;
        data->callback = callback;
        data->entity_id = entity_id;
        mxRegTimers.push_back(data);
        return true;
    }

    bool RemoveTimer(const std::string& name)
    {
        return RemoveTimerData(name);
    }

    bool RemoveTimer(const std::string& name, const AFGUID& entity_id)
    {
        return RemoveTimerData(name, entity_id);
    }

    uint32_t FindLeftTime(const std::string& name, const AFGUID& entity_id)
    {
        //TODO:
        return 0;
    }

protected:
    void UpdateTimer()
    {
        //TODO:��Ҫ�滻Ϊһ��ͳһ��ϵͳʱ��
        uint64_t now = AFCTimeBase::GetInstance().GetNowMillisecond();
        uint16_t passedSlot = (now - mnLastUpdateTime) / SLOT_TIME;
        if (passedSlot == 0)
        {
            return;
        }

        mnLastUpdateTime += passedSlot * SLOT_TIME;
        for (uint16_t i = 0; i < passedSlot; ++i)
        {
            mnNowSlot = (mnNowSlot + 1) % MAX_SLOT;
            UpdateSlotTimer();
        }
    }

    void UpdateTimerReg()
    {
        if (mxRegTimers.empty())
        {
            return;
        }

        for (auto data : mxRegTimers)
        {
            switch (data->type)
            {
            case TIMER_TYPE_FOREVER:
                AddSlotTimer(data, true);
                break;
            case TIMER_TYPE_COUNT_LIMIT:
                AddSlotTimer(data, false);
                break;
            default:
                ARK_ASSERT_NO_EFFECT(0);
                break;
            }
        }

        mxRegTimers.clear();
    }

    AFTimerData* FindTimerData(const std::string& name, const AFGUID& entity_id)
    {
        auto iter = mxTimers.find(name);
        if (iter == mxTimers.end())
        {
            return nullptr;
        }

        auto it = iter->second.find(entity_id);
        if (it == iter->second.end())
        {
            return nullptr;
        }

        return it->second;
    }

    bool AddTimerData(const std::string& name, const AFGUID& entity_id, AFTimerData* timer_data)
    {
        auto& iter = mxTimers.find(name);
        if (iter == mxTimers.end())
        {
            std::map<AFGUID, AFTimerData*> tmp;
            iter = mxTimers.insert(std::make_pair(name, tmp)).first;
        }

        return iter->second.insert(std::make_pair(entity_id, timer_data)).second;
    }

    bool RemoveTimerData(const std::string& name)
    {
        auto iter = mxTimers.find(name);
        if (iter == mxTimers.end())
        {
            return false;
        }

        for (auto it : iter->second)
        {
            AFTimerData* data = it.second;
            RemoveSlotTimer(data);
            ARK_DELETE(data);
        }

        iter->second.clear();
        mxTimers.erase(iter);
        return true;
    }

    bool RemoveTimerData(const std::string& name, const AFGUID& entity_id)
    {
        auto iter = mxTimers.find(name);
        if (iter == mxTimers.end())
        {
            return false;
        }

        auto it = iter->second.find(entity_id);
        if (it == iter->second.end())
        {
            return false;
        }

        AFTimerData* data = it->second;
        RemoveSlotTimer(data);
        ARK_DELETE(data);

        iter->second.erase(it);
        if (iter->second.empty())
        {
            mxTimers.erase(iter);
        }

        return true;
    }

    void AddSlotTimer(AFTimerData* timer_data, bool first)
    {
        if (first)
        {
            timer_data->rotation = 0;
            timer_data->slot = (mnNowSlot + 1) % MAX_SLOT;
        }
        else
        {
            uint32_t ticks = timer_data->interval / SLOT_TIME;
            timer_data->rotation = ticks / MAX_SLOT;
            timer_data->slot = ((ticks % MAX_SLOT) + mnNowSlot) % MAX_SLOT;
        }

        auto wheelData = mxSlots[timer_data->slot];
        if (wheelData != nullptr)
        {
            timer_data->next = wheelData;
            wheelData->prev = timer_data;
        }

        mxSlots[timer_data->slot] = timer_data;
    }

    void RemoveSlotTimer(AFTimerData* timer_data)
    {
        auto prev = timer_data->prev;
        if (prev != nullptr)
        {
            prev->next = timer_data->next;
        }

        auto next = timer_data->next;
        if (next != nullptr)
        {
            next->prev = timer_data->prev;
        }

        if (timer_data == mxSlots[timer_data->slot])
        {
            mxSlots[timer_data->slot] = next;
        }

        timer_data->prev = nullptr;
        timer_data->next = nullptr;
    }

    void UpdateSlotTimer()
    {
        std::list<AFTimerData*> doneDatas;
        auto timerData = mxSlots[mnNowSlot];
        while (timerData != nullptr)
        {
            if (timerData->rotation > 0)
            {
                --timerData->rotation;
            }
            else
            {
                doneDatas.push_back(timerData);
            }

            timerData = timerData->next;
        }

        for (auto data : doneDatas)
        {
            RemoveSlotTimer(data);

            (*(data->callback))(data->name, data->entity_id);
            switch (data->type)
            {
            case TIMER_TYPE_FOREVER:
                AddSlotTimer(data, false);
                break;
            case TIMER_TYPE_COUNT_LIMIT:
                {
                    --data->count;
                    if (data->count == 0)
                    {
                        RemoveTimerData(data->name, data->entity_id);
                    }
                    else
                    {
                        AddSlotTimer(data, false);
                    }
                }
                break;
            default:
                RemoveTimerData(data->name, data->entity_id);
                break;
            }
        }
    }

private:
    uint16_t mnNowSlot;
    AFTimerData* mxSlots[MAX_SLOT];
    uint64_t mnLastUpdateTime;
    std::map<std::string, std::map<AFGUID, AFTimerData*>> mxTimers;
    std::list<AFTimerData*> mxRegTimers;
};