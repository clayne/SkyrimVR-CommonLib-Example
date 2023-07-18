#include <spdlog/sinks/basic_file_sink.h>

#include "SKSE/API.h"
#include "SKSE/Impl/Stubs.h"
#include "VRExample.h"
#include "higgsinterface001.h"


void MessageListener(SKSE::MessagingInterface::Message *message);
void SetupLog();
void InitializeHooks();

// Interface for communicating with other SKSE plugins.
static SKSE::detail::SKSEMessagingInterface *g_messaging;
static SKSE::PluginHandle g_pluginHandle = 0xFFFFFFFF;

/// Main plugin entry point.
SKSEPluginLoad(const SKSE::LoadInterface *skse)
{
    SKSE::Init(skse);
    SetupLog();

    SKSE::GetMessagingInterface()->RegisterListener(MessageListener);

    g_pluginHandle = skse->GetPluginHandle();
    g_messaging = (SKSE::detail::SKSEMessagingInterface *)skse->QueryInterface(SKSE::LoadInterface::kMessaging);
    VRExample::g_task = (SKSE::detail::SKSETaskInterface *)(skse->QueryInterface(SKSE::LoadInterface::kTask));

    return true;
}

/// Receives messages about the game's state that SKSE broadcasts to all plugins.
void MessageListener(SKSE::MessagingInterface::Message *message)
{
    using namespace SKSE::log;

    switch (message->type)
    {
    case SKSE::MessagingInterface::kPostLoad:
        info("kPostLoad: sent to registered plugins once all plugins have been loaded");
        break;

    case SKSE::MessagingInterface::kPostPostLoad:
        info("kPostPostLoad: querying higgs interface");
        g_higgsInterface = HiggsPluginAPI::GetHiggsInterface001(g_pluginHandle, g_messaging);
        if (g_higgsInterface)
        {
            info("Got higgs interface");
        }
        break;

    case SKSE::MessagingInterface::kInputLoaded:
        info("kInputLoaded: sent right after game input is loaded, right before the main menu initializes");
        break;

    case SKSE::MessagingInterface::kDataLoaded:
        info("kDataLoaded: sent after the data handler has loaded all its forms");
        // Initialize our mod.
        VRExample::StartMod();

        break;

    case SKSE::MessagingInterface::kPreLoadGame:
        info("kPreLoadGame: sent immediately before savegame is read");
        break;

    case SKSE::MessagingInterface::kPostLoadGame:
        info("kPostLoadGame: sent after an attempt to load a saved game has finished");
        VRExample::GameLoad();
        break;

    case SKSE::MessagingInterface::kSaveGame:
        info("kSaveGame");
        break;

    case SKSE::MessagingInterface::kDeleteGame:
        info("kDeleteGame: sent right before deleting the .skse cosave and the .ess save");
        break;

    case SKSE::MessagingInterface::kNewGame:
        info("kNewGame: sent after a new game is created, before the game has loaded");
        break;

    default:
        info("Unknown system message of type: {}", message->type);
        break;
    }
}

/// Initialize logging system.
void SetupLog()
{
    auto logsFolder = SKSE::log::log_directory();
    if (!logsFolder)
    {
        SKSE::stl::report_and_fail("SKSE log_directory not provided, logs disabled.");
        return;
    }
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
    auto logFilePath = *logsFolder / std::format("{}.log", pluginName);
    auto fileLoggerPtr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true);
    auto loggerPtr = std::make_shared<spdlog::logger>("log", std::move(fileLoggerPtr));
    spdlog::set_default_logger(std::move(loggerPtr));
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::info);
}
