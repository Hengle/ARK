// -------------------------------------------------------------------------
//    @FileName         :    AFCPropertyMgr.h
//    @Author           :    Ark Game Tech
//    @Date             :    2012-03-01
//    @Module           :    AFCPropertyMgr
//
// -------------------------------------------------------------------------

#pragma once

#include "AFDefine.h"
#include "AFCDataList.h"
#include "AFString.hpp"
#include "AFArrayPod.hpp"
#include "AFStringPod.hpp"
#include "AFCData.h"

using namespace ArkFrame;

struct AFProperty
{
    PropertyName name; //�����������16���ַ�
    AFXData value;    //����ֵ

    //TODO:��ʱ��û����
    bool bPublic;
    bool bPrivate;
    bool bSave;
    bool bRealtime;
};

class AFPropertyMgr
{
public:

    AFPropertyMgr();
    ~AFPropertyMgr();
    void Clear();

    //bool RegisterCallback(const std::string& strProperty, const PROPERTY_EVENT_FUNCTOR_PTR& cb);
    bool AddProperty(const char* name, const AFXData& value, bool bPublic, bool bPrivate, bool bSave, bool bRealTime);

    bool SetProperty(const char* name, const AFXData& value);

    bool SetPropertyBool(const char* name, const bool value);
    bool SetPropertyInt(const char* name, const int32_t value);
    bool SetPropertyInt64(const char* name, const int64_t value);
    bool SetPropertyFloat(const char* name, const float value);
    bool SetPropertyDouble(const char* name, const double value);
    bool SetPropertyString(const char* name, const std::string& value);
    bool SetPropertyObject(const char* name, const AFGUID& value);

    bool GetPropertyBool(const char* name);
    int32_t GetPropertyInt(const char* name);
    int64_t GetPropertyInt64(const char* name);
    float GetPropertyFloat(const char* name);
    double GetPropertyDouble(const char* name);
    const char* GetPropertyString(const char* name);
    const AFGUID& GetPropertyObject(const char* name);

protected:
    bool FindIndex(const char* name, size_t& index);

private:
    ArraryPod<AFProperty*, 1, CoreAlloc> mxPropertys;
    StringPod<char, size_t, StringTraits<char>, CoreAlloc> mxIndices;
};
