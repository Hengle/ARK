#include "HelloWorld2.h"
#include "SDK/Core/AFCObject.h"
#include "SDK/Core/AFIComponent.h"

bool HelloWorld2::Init()
{
    //��ʼ��

    std::cout << "Hello, world2, Init" << std::endl;

    return true;
}

int HelloWorld2::OnPropertyCallBackEvent(const AFGUID& self, const std::string& strProperty, const AFIData& oldVar, const AFIData& newVar)
{
    //���Իص��¼���ֻҪ����ֵ�����б仯���ͻᱻ�ص�
    std::cout << "OnPropertyCallBackEvent Property: " << strProperty << " OldValue: " << oldVar.GetInt() << " NewValue: " << newVar.GetInt() << std::endl;

    return 0;
}

bool HelloWorld2::AfterInit()
{
    AFIDataList xData;
    xData.AddInt(111);




// #ifdef NF_USE_ACTOR
//     if(pPluginManager->GetActorID() == AFIActorManager::EACTOR_MAIN)
// #endif
    {
        std::cout << "Hello, world2, AfterInit" << std::endl;

        //created a object for this test
        AFIObject* pObject = new AFCObject(AFGUID(0, 1), pPluginManager);

        //add a property name is "Hello" of this object
        pObject->GetPropertyManager()->AddProperty(pObject->Self(), "Hello", DT_STRING);
        //add a property name is "World" of this object
        pObject->GetPropertyManager()->AddProperty(pObject->Self(), "World", DT_INT);

        //set the "world" property value as 1111
        pObject->SetPropertyInt("World", 1111);
        int n1 = pObject->GetPropertyInt("World");
        //get the "world" property value and printf it
        const int nProperty1 = pObject->GetPropertyInt("World");
        std::cout << "Property World:" << nProperty1 << std::endl;

        //add a call back functin for "world" property
        pObject->AddPropertyCallBack("World", this, &HelloWorld2::OnPropertyCallBackEvent);

        ////set the "world" property value as 2222[than the function "HelloWorld2::OnPropertyCallBackEvent" will be called]
        pObject->SetPropertyInt("World", 2222);
        int n2 = pObject->GetPropertyInt("World");

        //get the "world" property value and printf it
        const int nProperty2 = pObject->GetPropertyInt("World");
        std::cout << "Property World:" << nProperty2 << std::endl;

    }

    return true;
}

bool HelloWorld2::Execute()
{
    //ÿִ֡��
    //std::cout << "Hello, world2, Execute" << std::endl;

    return true;
}

bool HelloWorld2::BeforeShut()
{
    //����ʼ��֮ǰ
    std::cout << "Hello, world2, BeforeShut" << std::endl;

    return true;
}

bool HelloWorld2::Shut()
{
    //����ʼ��
    std::cout << "Hello, world2, Shut" << std::endl;

    return true;
}
