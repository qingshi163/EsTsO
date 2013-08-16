#include "StdAfx.h"
#include "tsremote.h"
namespace TSRemote
{

TtsrGetLastError GetLastError;
TtsrConnect Connect;
TtsrDisconnect Disconnect;
TtsrQuit Quit;
TtsrSwitchChannelName SwitchChannelName;
TtsrSwitchChannelID SwitchChannelID;
TtsrGetVersion GetVersion;
TtsrGetServerInfo GetServerInfo;
TtsrGetUserInfo GetUserInfo;
TtsrGetChannelInfoByID GetChannelInfoByID;
TtsrGetChannelInfoByName GetChannelInfoByName;
TtsrGetPlayerInfoByID GetPlayerInfoByID;
TtsrGetPlayerInfoByName GetPlayerInfoByName;
TtsrGetChannels GetChannels;
TtsrGetPlayers GetPlayers;
TtsrGetSpeakers GetSpeakers;
TtsrSetPlayerFlags SetPlayerFlags;
TtsrSetWantVoiceReason SetWantVoiceReason;
TtsrSetOperator SetOperator;
TtsrSetVoice SetVoice;
TtsrKickPlayerFromServer KickPlayerFromServer;
TtsrKickPlayerFromChannel KickPlayerFromChannel;
TtsrSendTextMessageToChannel SendTextMessageToChannel;
TtsrSendTextMessage SendTextMessage;

HMODULE g_handle = NULL;

int InitTsRemoteLibrary(const char *LibName)
{
    if (g_handle != NULL)
        return -1;

    g_handle = LoadLibrary(LibName);

    if (g_handle == NULL)
    {
        //int err = GetLastError();
        return -2;
    }
    
    GetLastError = (TtsrGetLastError)GetProcAddress(g_handle, "tsrGetLastError");
    Connect = (TtsrConnect)GetProcAddress(g_handle, "tsrConnect");
    Disconnect = (TtsrDisconnect)GetProcAddress(g_handle, "tsrDisconnect");
    Quit = (TtsrQuit)GetProcAddress(g_handle, "tsrQuit");
    SwitchChannelName = (TtsrSwitchChannelName)GetProcAddress(g_handle, "tsrSwitchChannelName");
    SwitchChannelID = (TtsrSwitchChannelID)GetProcAddress(g_handle, "tsrSwitchChannelID");
    GetVersion = (TtsrGetVersion)GetProcAddress(g_handle, "tsrGetVersion");
    GetServerInfo = (TtsrGetServerInfo)GetProcAddress(g_handle, "tsrGetServerInfo");
    GetUserInfo = (TtsrGetUserInfo)GetProcAddress(g_handle, "tsrGetUserInfo");
    GetChannelInfoByID = (TtsrGetChannelInfoByID)GetProcAddress(g_handle, "tsrGetChannelInfoByID");
    GetChannelInfoByName = (TtsrGetChannelInfoByName)GetProcAddress(g_handle, "tsrGetChannelInfoByName");
    GetPlayerInfoByID = (TtsrGetPlayerInfoByID)GetProcAddress(g_handle, "tsrGetPlayerInfoByID");
    GetPlayerInfoByName = (TtsrGetPlayerInfoByName)GetProcAddress(g_handle, "tsrGetPlayerInfoByName");
    GetChannels = (TtsrGetChannels)GetProcAddress(g_handle, "tsrGetChannels");
    GetPlayers = (TtsrGetPlayers)GetProcAddress(g_handle, "tsrGetPlayers");
    GetSpeakers = (TtsrGetSpeakers)GetProcAddress(g_handle, "tsrGetSpeakers");
    SetPlayerFlags = (TtsrSetPlayerFlags)GetProcAddress(g_handle, "tsrSetPlayerFlags");
    SetWantVoiceReason = (TtsrSetWantVoiceReason)GetProcAddress(g_handle, "tsrSetWantVoiceReason");
    SetOperator = (TtsrSetOperator)GetProcAddress(g_handle, "tsrSetOperator");
    SetVoice = (TtsrSetVoice)GetProcAddress(g_handle, "tsrSetVoice");
    KickPlayerFromServer = (TtsrKickPlayerFromServer)GetProcAddress(g_handle, "tsrKickPlayerFromServer");
    KickPlayerFromChannel = (TtsrKickPlayerFromChannel)GetProcAddress(g_handle, "tsrKickPlayerFromChannel");
    SendTextMessageToChannel = (TtsrSendTextMessageToChannel)GetProcAddress(g_handle, "tsrSendTextMessageToChannel");
    SendTextMessage = (TtsrSendTextMessage)GetProcAddress(g_handle, "tsrSendTextMessage");

    // Check all function is ok
    if (GetLastError && Connect && Disconnect && Quit && SwitchChannelName && SwitchChannelID && GetVersion &&
        GetServerInfo && GetUserInfo && GetChannelInfoByID && GetChannelInfoByName && GetChannels && GetPlayers &&
        GetSpeakers && SetPlayerFlags && SetWantVoiceReason && SetOperator && SetVoice && KickPlayerFromServer &&
        KickPlayerFromChannel && SendTextMessageToChannel && SendTextMessage)
    {
        return 0;
    }

    // Error here, unload library
    CloseTsRemoteLibrary();
    return -3;
}

int CloseTsRemoteLibrary()
{
    if (g_handle == NULL)
        return -1;

    FreeLibrary(g_handle);

    g_handle = NULL;

    return 0;
}

}