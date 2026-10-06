#include "Application.hpp"
#include "App/Environment.hpp"
#include "App/Migration.hpp"
#include "App/Project.hpp"
#include "App/Stats/StatService.hpp"
#include "App/Tweaks/TweakService.hpp"
#include "Core/Foundation/RuntimeProvider.hpp"
#include "Support/RED4ext/RED4extProvider.hpp"
#include "Support/RedLib/RedLibProvider.hpp"
#include "Support/Spdlog/SpdlogProvider.hpp"
#ifndef __APPLE__
#include "Support/MinHook/MinHookProvider.hpp"
#endif

App::Application::Application(HMODULE aHandle, const RED4ext::v1::Sdk* aSdk)
{
    // On macOS the game .app bundle layout is: .app/Contents/MacOS/<exe>
    // Walking up 3 parents from the exe reaches the game root directory.
    const int pathDepth = 3;
#ifndef __APPLE__
    const int winPathDepth = 2;
#endif

    Register<Core::RuntimeProvider>(aHandle)
#ifdef __APPLE__
        ->SetBaseImagePathDepth(pathDepth);
#else
        ->SetBaseImagePathDepth(winPathDepth);
#endif

#ifndef __APPLE__
    Register<Support::MinHookProvider>();
#endif
    Register<Support::SpdlogProvider>()
        ->AppendTimestampToLogName()
        ->CreateRecentLogSymlink();
    Register<Support::RED4extProvider>(aHandle, aSdk)
        ->EnableAddressLibrary()
        ->EnableHooking()
        ->RegisterScripts(Env::PluginScriptsDir());
    Register<Support::RedLibProvider>();

    Register<App::TweakService>(Env::GameVer(), Env::GameDir(), Env::TweaksDir(),
                                Env::InheritanceMapPath(), Env::ExtraFlatsPath(),
                                Env::RedModSourcesDir());
#ifndef __APPLE__
    Register<App::StatService>(); // macOS: StatsDataSystem functions are not located yet
#endif
}

void App::Application::OnStarting()
{
    LogInfo("{} {} is starting...", Project::Name, Project::Version.to_string());

    Migration::CleanUp(Env::LegacyScriptsDir());
}
