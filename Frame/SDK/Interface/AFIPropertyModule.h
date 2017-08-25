/*****************************************************************************
// * This source file is part of ArkGameFrame                                *
// * For the latest info, see https://github.com/ArkGame                     *
// *                                                                         *
// * Copyright(c) 2013 - 2017 ArkGame authors.                               *
// *                                                                         *
// * Licensed under the Apache License, Version 2.0 (the "License");         *
// * you may not use this file except in compliance with the License.        *
// * You may obtain a copy of the License at                                 *
// *                                                                         *
// *     http://www.apache.org/licenses/LICENSE-2.0                          *
// *                                                                         *
// * Unless required by applicable law or agreed to in writing, software     *
// * distributed under the License is distributed on an "AS IS" BASIS,       *
// * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*
// * See the License for the specific language governing permissions and     *
// * limitations under the License.                                          *
// *                                                                         *
// *                                                                         *
// * @FileName  AFIPropertyModule.h                                                *
// * @Author    Ark Game Tech                                                *
// * @Date      2015-12-15                                                   *
// * @Module    AFIPropertyModule                                                  *
// * @email     ArkGameTech@163.com                                          *
// * @brief     AFIPropertyModule                                                  *
*****************************************************************************/
#ifndef AFI_PROPERTY_MODULE_H
#define AFI_PROPERTY_MODULE_H

#include <iostream>
#include "AFIModule.h"

class AFIPropertyModule
    : public AFIModule
{
public:
    enum NFPropertyGroup
    {
        NPG_JOBLEVEL,        //ְҵ�ȼ�����
        NPG_EFFECTVALUE,     //һ������Ӱ��������ԵĲ���(ֱ���ù�ʽ���㣬�������ֲ��ö�)
        NPG_REBIRTH_ADD,     //��������
        NPG_EQUIP,           //װ������Ӱ������֮��ĵ���2�μ���(ֱ�Ӳ�Ҫ��������ʲô��)
        NPG_EQUIP_AWARD,     //��װ����
        NPG_STATIC_BUFF,     //�������͵�BUFF���츳֮��ģ����߳Ե�����ҩˮ

        NPG_RUNTIME_BUFF,    //��̬BUFF

        NPG_ALL,
    };


    virtual int RefreshBaseProperty(const AFGUID& self) = 0;
    virtual int GetPropertyValue(const AFGUID& self, const std::string& strPropertyName, const NFPropertyGroup eGroupType) = 0;
    virtual int SetPropertyValue(const AFGUID& self, const std::string& strPropertyName, const NFPropertyGroup eGroupType, const int nValue) = 0;
    virtual int AddPropertyValue(const AFGUID& self, const std::string& strPropertyName, const NFPropertyGroup eGroupType, const int nValue) = 0;
    virtual int SubPropertyValue(const AFGUID& self, const std::string& strPropertyName, const NFPropertyGroup eGroupType, const int nValue) = 0;

    virtual bool FullHPMP(const AFGUID& self) = 0;
    virtual bool AddHP(const AFGUID& self, const int64_t& nValue) = 0;
    virtual bool ConsumeHP(const AFGUID& self, const int64_t& nValue) = 0;
    virtual bool EnoughHP(const AFGUID& self, const int64_t& nValue) = 0;

    virtual bool AddMP(const AFGUID& self, const int64_t& nValue) = 0;
    virtual bool ConsumeMP(const AFGUID& self, const int64_t& nValue) = 0;
    virtual bool EnoughMP(const AFGUID& self, const int64_t& nValue) = 0;

    virtual bool FullSP(const AFGUID& self) = 0;
    virtual bool AddSP(const AFGUID& self, const int64_t& nValue) = 0;
    virtual bool ConsumeSP(const AFGUID& self, const int64_t& nValue) = 0;
    virtual bool EnoughSP(const AFGUID& self, const int64_t& nValue) = 0;

    virtual bool AddMoney(const AFGUID& self, const int64_t& nValue) = 0;
    virtual bool ConsumeMoney(const AFGUID& self, const int64_t& nValue) = 0;
    virtual bool EnoughMoney(const AFGUID& self, const int64_t& nValue) = 0;

    virtual bool AddDiamond(const AFGUID& self, const int64_t& nValue) = 0;
    virtual bool ConsumeDiamond(const AFGUID& self, const int64_t& nValue) = 0;
    virtual bool EnoughDiamond(const AFGUID& self, const int64_t& nValue) = 0;
};

#endif
