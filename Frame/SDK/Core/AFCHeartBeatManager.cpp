// -------------------------------------------------------------------------
//    @FileName         :    AFCHeartBeatManager.cpp
//    @Author           :    Ark Game Tech
//    @Date             :    2012-12-17
//    @Module           :    AFCHeartBeatManager
//
// -------------------------------------------------------------------------

#include "AFCHeartBeatManager.h"
#include "AFTime.h"

AFCHeartBeatManager::~AFCHeartBeatManager()
{
    mHeartBeatElementMapEx.ClearAll();
}

void AFCHeartBeatElement::DoHeartBeatEvent()
{
    HEART_BEAT_FUNCTOR_PTR cb;
    bool bRet = First(cb);
    while(bRet)
    {
        (*cb)(self, strBeatName, nBeatTime, nCount);

        bRet = Next(cb);
    }
}
//////////////////////////////////////////////////////////////////////////
bool AFCHeartBeatManager::Execute()
{
    //millisecond
    AFINT64 nTime = AFTime::GetNowMillisecond();
    AFCHeartBeatElement* pElement = mHeartBeatElementMapEx.FirstNude();
    while(nullptr != pElement)
    {
        if(nTime > pElement->nNextTriggerTime && pElement->nCount > 0)
        {
            pElement->nCount--;

            pElement->DoHeartBeatEvent();

            if(pElement->nCount <= 0)
            {
                //�ȴ�ɾ��
                mRemoveListEx.Add(pElement->strBeatName);
            }
            else
            {
                //Do Event
                pElement->nNextTriggerTime = nTime + pElement->nBeatTime;
            }
        }

        pElement = mHeartBeatElementMapEx.NextNude();
    }

    //ɾ�����й�ʱ����
    std::string strHeartBeatName;
    bool bRet = mRemoveListEx.First(strHeartBeatName);
    while(bRet)
    {
        mHeartBeatElementMapEx.RemoveElement(strHeartBeatName);

        bRet = mRemoveListEx.Next(strHeartBeatName);
    }

    mRemoveListEx.ClearAll();

    //////////////////////////////////////////////////////////////////////////
    //���������Ҳ����ʱ��ӵ�
    for(std::list<AFCHeartBeatElement>::iterator iter = mAddListEx.begin(); iter != mAddListEx.end(); ++iter)
    {
        if(NULL == mHeartBeatElementMapEx.GetElement(iter->strBeatName))
        {
            NF_SHARE_PTR<AFCHeartBeatElement> pHeartBeatEx(NF_NEW AFCHeartBeatElement());
            *pHeartBeatEx = *iter;
            mHeartBeatElementMapEx.AddElement(pHeartBeatEx->strBeatName, pHeartBeatEx);
        }
    }

    mAddListEx.clear();

    return true;
}

bool AFCHeartBeatManager::RemoveHeartBeat(const std::string& strHeartBeatName)
{
    return mRemoveListEx.Add(strHeartBeatName);
}

AFGUID AFCHeartBeatManager::Self()
{
    return mSelf;
}

//////////////////////////////////////////////////////////////////////////
bool AFCHeartBeatManager::AddHeartBeat(const AFGUID self, const std::string& strHeartBeatName, const HEART_BEAT_FUNCTOR_PTR& cb, const AFINT64 nTime, const int nCount)
{
    AFCHeartBeatElement xHeartBeat;
    xHeartBeat.nNextTriggerTime = AFTime::GetNowMillisecond() + nTime;
    xHeartBeat.nBeatTime = nTime;
    xHeartBeat.nCount = nCount;
    xHeartBeat.self = self;
    xHeartBeat.strBeatName = strHeartBeatName;
    xHeartBeat.Add(cb);
    mAddListEx.push_back(xHeartBeat);

    return true;
}

bool AFCHeartBeatManager::Exist(const std::string& strHeartBeatName)
{
    if(mHeartBeatElementMapEx.GetElement(strHeartBeatName))
    {
        return true;
    }

    return false;
}
