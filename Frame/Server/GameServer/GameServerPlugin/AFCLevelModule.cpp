// -------------------------------------------------------------------------
//    @FileName			:    AFCLevelModule.h
//    @Author           :    Ark Game Tech
//    @Date             :    2013-09-28
//    @Module           :    AFCLevelModule
//
// -------------------------------------------------------------------------

#include "AFCLevelModule.h"

bool AFCLevelModule::Init()
{
    return true;
}


bool AFCLevelModule::Shut()
{
    return true;
}

bool AFCLevelModule::Execute()
{
    //λ����
    return true;
}

bool AFCLevelModule::AfterInit()
{
    m_pKernelModule = pPluginManager->FindModule<AFIKernelModule>();
    m_pLogModule = pPluginManager->FindModule<AFILogModule>();
    m_pPropertyConfigModule = pPluginManager->FindModule<AFIPropertyConfigModule>();
    m_pElementModule = pPluginManager->FindModule<AFIElementModule>();

    return true;
}

int AFCLevelModule::AddExp(const AFGUID& self, const int nExp)
{
    int eJobType = m_pKernelModule->GetPropertyInt(self, NFrame::Player::Job());
    int nCurExp = m_pKernelModule->GetPropertyInt(self, NFrame::Player::EXP());
    int nLevel = m_pKernelModule->GetPropertyInt(self, NFrame::Player::Level());
    int nMaxExp = m_pPropertyConfigModule->CalculateBaseValue(eJobType, nLevel, NFrame::Player::MAXEXP());

    nCurExp += nExp;

    int nRemainExp = nCurExp - nMaxExp;
    while (nRemainExp >= 0)
    {
        //����
        nLevel++;
        //��ֹԽ��BUG
        m_pKernelModule->SetPropertyInt(self, NFrame::Player::Level(), nLevel);

        nCurExp = nRemainExp;

        nMaxExp = m_pPropertyConfigModule->CalculateBaseValue(eJobType, nLevel, NFrame::Player::MAXEXP());
        if (nMaxExp <= 0)
        {
            break;
        }

        nRemainExp -= nMaxExp;
    }

    m_pKernelModule->SetPropertyInt(self, NFrame::Player::EXP(), nCurExp);

    return 0;
}
