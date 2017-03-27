#include "HelloWorld3Module.h"
#include "NFComm/NFMessageDefine/NFProtocolDefine.hpp"

bool HelloWorld3Module::Init()
{
    //��ʼ��
    std::cout << "Hello, world3, Init" << std::endl;

    return true;
}

int HelloWorld3Module::OnEvent(const NFGUID& self, const int event, const AFDataList& arg)
{
    //�¼��ص�����
    std::cout << "OnEvent EventID: " << event << " self: " << self.nData64 << " argList: " << arg.Int(0) << " " << " " << arg.String(1) << std::endl;

    m_pKernelModule->SetPropertyInt(self, "Hello", arg.Int(0));
    m_pKernelModule->SetPropertyString(self, "Hello", arg.String(1));

    return 0;
}

int HelloWorld3Module::OnHeartBeat(const NFGUID& self, const std::string& strHeartBeat, const float fTime, const int nCount)
{

    unsigned long unNowTime = NF_GetTickCount();

    std::cout << "strHeartBeat: " << fTime << " Count: " << nCount << "  TimeDis: " << unNowTime - mLastTime << std::endl;

    mLastTime = unNowTime;

    return 0;
}

int HelloWorld3Module::OnClassCallBackEvent(const NFGUID& self, const std::string& strClassName, const CLASS_OBJECT_EVENT event, const AFDataList& arg)
{
    //�������¼���ֻҪ�д������ഴ���������ټ���ص�
    std::cout << "OnClassCallBackEvent ClassName: " << strClassName << " ID: " << self.nData64 << " Event: " << event << std::endl;

    if(event == COE_CREATE_HASDATA)
    {
        m_pKernelModule->AddEventCallBack(self, 11111111, this, &HelloWorld3Module::OnEvent);

        m_pKernelModule->AddHeartBeat(self, "OnHeartBeat", this, &HelloWorld3Module::OnHeartBeat, 5.0f, 9999);

        mLastTime = NF_GetTickCount();
    }

    return 0;
}

int HelloWorld3Module::OnPropertyCallBackEvent(const NFGUID& self, const std::string& strProperty, const AFDataList::TData& oldVar, const AFDataList::TData& newVar)
{
    //���Իص��¼���ֻҪ����ֵ�����б仯���ͻᱻ�ص�
    std::cout << "OnPropertyCallBackEvent Property: " << strProperty << " OldValue: " << oldVar.GetInt() << " NewValue: " << newVar.GetInt() << std::endl;

    return 0;
}

int HelloWorld3Module::OnPropertyStrCallBackEvent(const NFGUID& self, const std::string& strProperty, const AFDataList::TData& oldVar, const AFDataList::TData& newVar)
{
    //���Իص��¼���ֻҪ����ֵ�����б仯���ͻᱻ�ص�
    std::cout << "OnPropertyCallBackEvent Property: " << strProperty << " OldValue: " << oldVar.GetString() << " NewValue: " << newVar.GetString() << std::endl;

    return 0;
}

bool HelloWorld3Module::AfterInit()
{
    //��ʼ�����
    std::cout << "Hello, world3, AfterInit" << std::endl;

    m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();
    m_pElementModule = pPluginManager->FindModule<NFIElementModule>();

    //�������������еĶ��������������
    m_pKernelModule->CreateScene(1);

    m_pKernelModule->AddClassCallBack(NFrame::Player::ThisName(), this, &HelloWorld3Module::OnClassCallBackEvent);

    //�������󣬹���ص������Իص�,Ȼ���¼��������
    NF_SHARE_PTR<NFIObject> pObject = m_pKernelModule->CreateObject(NFGUID(0, 10), 1, 0, NFrame::Player::ThisName(), "", AFDataList());
    if(nullptr == pObject)
    {
        return false;
    }

    pObject->GetPropertyManager()->AddProperty(pObject->Self(), "Hello", TDATA_STRING);
    pObject->GetPropertyManager()->AddProperty(pObject->Self(), "World", TDATA_INT);

    pObject->AddPropertyCallBack("Hello", this, &HelloWorld3Module::OnPropertyStrCallBackEvent);
    pObject->AddPropertyCallBack("World", this, &HelloWorld3Module::OnPropertyCallBackEvent);

    pObject->SetPropertyString("Hello", "hello,World");
    pObject->SetPropertyInt("World", 1111);

    m_pKernelModule->DoEvent(pObject->Self(), 11111111, AFDataList() << int(100) << "200");


    //for(int i = 0; i < 100000; ++i)
    //{
    //    AFDataList testData;
    //    testData << 1 << 5656.22f << "sdfgsdgsdfsdfds" << NFGUID(33, 55) << Point3D(1, 3, 4);

    //    AFDataList testData2;
    //    testData2 << 1 << 5656.22f << "sdfgsdgsdfsdfds" << NFGUID(33, 55) << Point3D(1, 3, 4);


    //    testData2.Append(testData);

    //    AFDataList testData3;

    //    testData3 = testData2;

    //}

    return true;
}

bool HelloWorld3Module::Execute()
{
    //ÿִ֡��
    //std::cout << "Hello, world3, Execute" << std::endl;

    return true;
}

bool HelloWorld3Module::BeforeShut()
{
    //����ʼ��֮ǰ
    std::cout << "Hello, world3, BeforeShut" << std::endl;

    m_pKernelModule->DestroyAll();

    return true;
}

bool HelloWorld3Module::Shut()
{
    //����ʼ��
    std::cout << "Hello, world3, Shut" << std::endl;

    return true;
}
