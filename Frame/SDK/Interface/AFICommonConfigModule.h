// -------------------------------------------------------------------------
//    @FileName         ��    AFICommonConfigModule.h
//    @Author           ��    Ark Game Tech
//    @Date             ��    2012-12-15
//    @Module           ��    AFICosmmonConfigModule
//
// -------------------------------------------------------------------------

#ifndef AFI_COMMONCOAFIG_MODULE_H
#define AFI_COMMONCOAFIG_MODULE_H

#include <iostream>
#include "AFILogicModule.h"
#include "AFIBuffConfigModule.h"


class AFICommonConfigModule
    : public AFILogicModule
{
public:
    virtual bool ClearConfig() = 0;
    virtual const int GetAttributeInt(const std::string& strStructName, const std::string& strStructItemName, const std::string& strAttribute) = 0;
    virtual const int GetAttributeInt(const std::string& strStructName, const std::string& strSDKAttribute) = 0;
    virtual const std::string& GetAttributeString(const std::string& strStructName, const std::string& strStructItemName, const std::string& strAttribute) = 0;
    virtual const std::string& GetAttributeString(const std::string& strStructName, const std::string& strSDKAttribute) = 0;
    virtual bool LoadConfig(const std::string& strFile) = 0;
    virtual const int GetStructItemList(const std::string& strStructName, std::vector<std::string>& xList) = 0;
};

#endif