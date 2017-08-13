#include "AFCWorldLogicModule.h"
#include "AFWorldLogicPlugin.h"

ARK_EXPORT void DllStartPlugin(AFIPluginManager* pm)
{
#if ARK_PLATFORM == PLATFORM_WIN
    SetConsoleTitle("ArkWorldServer");
#endif // ARK_PLATFORM
    CREATE_PLUGIN(pm, NFWorldLogicPlugin)
};

ARK_EXPORT void DllStopPlugin(AFIPluginManager* pm)
{
    DESTROY_PLUGIN(pm, NFWorldLogicPlugin)
};

//////////////////////////////////////////////////////////////////////////

const int NFWorldLogicPlugin::GetPluginVersion()
{
    return 0;
}

const std::string NFWorldLogicPlugin::GetPluginName()
{
    return GET_CLASS_NAME(NFWorldLogicPlugin);
}

void NFWorldLogicPlugin::Install()
{

    REGISTER_MODULE(pPluginManager, AFIWorldLogicModule, AFCWorldLogicModule)
}

void NFWorldLogicPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, AFIWorldLogicModule, AFCWorldLogicModule)
}
