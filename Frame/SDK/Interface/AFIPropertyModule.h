// -------------------------------------------------------------------------
//    @FileName         ��    AFIPropertyModule.h
//    @Author           ��    Ark Game Tech
//    @Date             ��    2012-12-15
//    @Module           ��    AFIPropertyModule
//
// -------------------------------------------------------------------------

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
        NPG_JOBLEVEL        ,//ְҵ�ȼ�����
        NPG_EFFECTVALUE     ,//һ������Ӱ��������ԵĲ���(ֱ���ù�ʽ���㣬�������ֲ��ö�)
        NPG_REBIRTH_ADD     ,//��������
        NPG_EQUIP           ,//װ������Ӱ������֮��ĵ���2�μ���(ֱ�Ӳ�Ҫ��������ʲô��)
        NPG_EQUIP_AWARD     ,//��װ����
        NPG_STATIC_BUFF     ,//�������͵�BUFF���츳֮��ģ����߳Ե�����ҩˮ

        NPG_RUNTIME_BUFF    ,//��̬BUFF

        NPG_ALL ,
    };


    virtual int RefreshBaseProperty(const AFGUID& self) = 0;
    virtual int GetPropertyValue(const AFGUID& self, const std::string& strPropertyName, const NFPropertyGroup eGroupType) = 0;
    virtual int SetPropertyValue(const AFGUID& self, const std::string& strPropertyName, const NFPropertyGroup eGroupType, const int nValue) = 0;
    virtual int AddPropertyValue(const AFGUID& self, const std::string& strPropertyName, const NFPropertyGroup eGroupType, const int nValue) = 0;
    virtual int SubPropertyValue(const AFGUID& self, const std::string& strPropertyName, const NFPropertyGroup eGroupType, const int nValue) = 0;

    virtual bool FullHPMP(const AFGUID& self) = 0;
    virtual bool AddHP(const AFGUID& self, const AFINT64& nValue) = 0;
    virtual bool ConsumeHP(const AFGUID& self, const AFINT64& nValue) = 0;
    virtual bool EnoughHP(const AFGUID& self, const AFINT64& nValue) = 0;

    virtual bool AddMP(const AFGUID& self, const AFINT64& nValue) = 0;
    virtual bool ConsumeMP(const AFGUID& self, const AFINT64& nValue) = 0;
    virtual bool EnoughMP(const AFGUID& self, const AFINT64& nValue) = 0;

    virtual bool FullSP(const AFGUID& self) = 0;
    virtual bool AddSP(const AFGUID& self, const AFINT64& nValue) = 0;
    virtual bool ConsumeSP(const AFGUID& self, const AFINT64& nValue) = 0;
    virtual bool EnoughSP(const AFGUID& self, const AFINT64& nValue) = 0;

    virtual bool AddMoney(const AFGUID& self, const AFINT64& nValue) = 0;
    virtual bool ConsumeMoney(const AFGUID& self, const AFINT64& nValue) = 0;
    virtual bool EnoughMoney(const AFGUID& self, const AFINT64& nValue) = 0;

    virtual bool AddDiamond(const AFGUID& self, const AFINT64& nValue) = 0;
    virtual bool ConsumeDiamond(const AFGUID& self, const AFINT64& nValue) = 0;
    virtual bool EnoughDiamond(const AFGUID& self, const AFINT64& nValue) = 0;
};

#endif