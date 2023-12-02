#include <swiftly/swiftly.h>
#include <swiftly/server.h>
#include <swiftly/database.h>
#include <swiftly/commands.h>
#include <swiftly/configuration.h>
#include <swiftly/logger.h>

#define CONNECTION_NAME "swiftly_mostactive"

Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Database *db = nullptr;
Commands *commands = nullptr;
Configuration *config = nullptr;
Logger *logger = nullptr;

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);

    server = new Server();
    g_playerManager = new PlayerManager();
    commands = new Commands(pluginName);
    config = new Configuration();
    logger = new Logger(mainFilePath, pluginName);
}

float CalculateHours(uint32_t seconds)
{
    return (seconds / 3600);
}

void Command_Hours(int playerID, const char **args, uint32_t argsCount, bool silent)
{
    if (playerID == -1)
        return;
    if (!db->IsConnected())
        return;

    Player *player = g_playerManager->GetPlayer(playerID);
    if (player == nullptr)
        return;

    DB_Result result = db->Query("select * from %s where steamid = '%llu' limit 1", config->Fetch<const char *>("mostactive.table_name"), player->GetSteamID());
    if (result.size() > 0)
        print(FetchTranslation("mostactive.current_hours"), config->Fetch<const char *>("mostactive.prefix"), CalculateHours(db->fetchValue<uint32_t>(result, 0, "connected_time") + player->GetConnectedTime()));
    else
        player->SendMsg(HUD_PRINTTALK, FetchTranslation("mostactive.no_entry"), config->Fetch<const char *>("mostactive.prefix"));
}

void OnPluginStart()
{
    if (config->Fetch<const char *>("mostactive.table_name") == "mostactive.table_name")
    {
        logger->Write(LOGLEVEL_ERROR, "[Most Active] You need to set a table value in configuration.");
        print("[Most Active] You need to set a table value in configuration.");
        return;
    }

    if (config->Fetch<const char *>("mostactive.hours_commands") == "mostactive.hours_commands")
    {
        logger->Write(LOGLEVEL_ERROR, "[Most Active] You need to set a command in configuration.");
        print("[Most Active] You need to set a command in configuration.");
        return;
    }

    db = new Database(CONNECTION_NAME);

    if (!db->IsConnected())
        return;

    DB_Result result = db->Query("CREATE TABLE IF NOT EXISTS `%s` (`steamid` varchar(128) NOT NULL, `connected_time` int(11) NOT NULL DEFAULT 0) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;", config->Fetch<const char *>("mostactive.table_name"));
    if (result.size() > 0)
        db->Query("ALTER TABLE `%s` ADD UNIQUE KEY `steamid` (`steamid`);", config->Fetch<const char *>("mostactive.table_name"));

    commands->Register(config->Fetch<const char *>("mostactive.hours_commands"), reinterpret_cast<void *>(&Command_Hours));

    logger->Write(LOGLEVEL_DEBUG, "Plugin started. Build Date: %s", __DATE__);
}

void OnPluginStop()
{
    logger->Write(LOGLEVEL_DEBUG, "Plugin stopped.");
}

void OnPlayerSpawn(Player *player)
{
    if (!db->IsConnected())
        return;

    if (player->IsFirstSpawn() && !player->IsFakeClient())
    {
        db->Query("insert ignore into %s (steamid) values ('%llu')", config->Fetch<const char *>("mostactive.table_name"), player->GetSteamID());
    }
}

void OnClientDisconnect(Player *player)
{
    if (!db->IsConnected())
        return;

    if (!player->IsFakeClient())
    {
        db->Query("update %s set connected_time = connected_time + %d where steamid = '%llu' limit 1", config->Fetch<const char *>("mostactive.table_name"), player->GetConnectedTime(), player->GetSteamID());
    }
}

const char *GetPluginAuthor()
{
    return "Swiftly Solutions";
}

const char *GetPluginVersion()
{
    return "1.0.0";
}

const char *GetPluginName()
{
    return "Most Active";
}

const char *GetPluginWebsite()
{
    return "https://github.com/swiftly-solution/swiftly_mostactive";
}