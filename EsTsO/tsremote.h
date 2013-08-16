#pragma once

namespace TSRemote
{

#define DECLARE_ENUM(E) \
struct E \
{ \
public: \
    E(int value = 0) : _value((__Enum)value) { \
    } \
    E& operator=(int value) { \
        this->_value = (__Enum)value; \
        return *this; \
    } \
    operator int() const { \
        return this->_value; \
    } \
\
    enum __Enum {

#define END_ENUM() \
    }; \
\
private: \
    __Enum _value; \
};

DECLARE_ENUM(Codecs)
    cmCelp51        = 1,
	cmCelp63        = 2,
	cmGSM148        = 4,
	cmGSM164        = 8,
	cmWindowsCELP52 = 16,
	SPEEX2150       = 32,  
	SPEEX3950       = 64, 
	SPEEX5950       = 128, 
	SPEEX8000       = 256, 
	SPEEX11000      = 512, 
	SPEEX15000      = 1024, 
	SPEEX18200      = 2048, 
	SPEEX24600      = 4096
END_ENUM()

DECLARE_ENUM(ChannelPrivileges)
	Admin        = 1,
	Operator     = 2,
	AutoOperator = 4,
	Voiced       = 8,
	AutoVoice    = 16
END_ENUM()

DECLARE_ENUM(UserPrivileges)
	SuperServerAdmin = 1,
	ServerAdmin      = 2,
	CanRegister      = 4,
	Registered       = 8,
	Unregistered     = 16
END_ENUM()

DECLARE_ENUM(PlayerFlags)
	ChannelCommander = 1,
	WantVoice        = 2,
	NoWhisper        = 4,
	Away             = 8,
	InputMuted       = 16,
	OutputMuted      = 32,
	Recording        = 64
END_ENUM()

DECLARE_ENUM(ChannelFlags)
	Registered   = 1,
	Unregistered = 2,
	Moderated    = 4,
	Password     = 8,
	Hierarchical = 16,
	Default      = 32
END_ENUM()

DECLARE_ENUM(ServerType)
	Clan       = 1,
	Public     = 2,
	Freeware   = 4,
	Commercial = 8
END_ENUM()

#undef DECLARE_ENUM
#undef END_ENUM

#pragma pack(1)

typedef struct TtsrPlayerInfo
{
    int PlayerID;
    int ChannelID;
    char NickName[30];
    int PlayerChannelPrivileges;
    int PlayerPrivileges;
    int PlayerFlags;
} PlayerInfo;

typedef struct TtsrChannelInfo
{
    int ChannelID;
    int ChannelParentID;
    int PlayerCountInChannel;
    int ChannelFlags;
    int Codec;
    char Name[30];
} ChannelInfo;

typedef struct TtsrVersion
{
    int Major;
    int Minor;
    int Release;
    int Build;
} Version;

typedef struct TtsrServerInfo
{
    char ServerName[30];
    char WelcomeMessage[256];
    int ServerVMajor;
    int ServerVMinor;
    int ServerVRelease;
    int ServerVBuild;
    char ServerPlatform[30];
    char ServerIp[30];
    char ServerHost[100];
    int ServerType;
    int ServerMaxUsers;
    int SupportedCodecs;
    int ChannelCount;
    int PlayerCount;
} ServerInfo;

typedef struct TtsrUserInfo
{
    TtsrPlayerInfo Player;
    TtsrChannelInfo Channel;
    TtsrChannelInfo ParentChannel;
} UserInfo;

#pragma pack()

typedef void (WINAPI *TtsrGetLastError)(char *pchBuffer, int BufferLength);
extern TtsrGetLastError GetLastError;

typedef int (WINAPI *TtsrConnect)(char *URL);
extern TtsrConnect Connect;

typedef int (WINAPI *TtsrDisconnect)();
extern TtsrDisconnect Disconnect;

typedef int (WINAPI *TtsrQuit)();
extern TtsrQuit Quit;

typedef int (WINAPI *TtsrSwitchChannelName)(char *ChannelName, char *ChannelPassword);
extern TtsrSwitchChannelName SwitchChannelName;

typedef int (WINAPI *TtsrSwitchChannelID)(int ChannelID, char *ChannelPassword);
extern TtsrSwitchChannelID SwitchChannelID;

typedef int (WINAPI*TtsrGetVersion)(Version *tsrVersion);
extern TtsrGetVersion GetVersion;

typedef int (WINAPI *TtsrGetServerInfo)(ServerInfo *tsrServerInfo);
extern TtsrGetServerInfo GetServerInfo;

typedef int (WINAPI *TtsrGetUserInfo)(UserInfo *tsrUserInfo);
extern TtsrGetUserInfo GetUserInfo;

typedef int (WINAPI *TtsrGetChannelInfoByID)(int ChannelID,
                                 ChannelInfo *tsrChannelInfo,
                                 PlayerInfo *tsrPlayerInfo,
                                 int *PlayerRecords);
extern TtsrGetChannelInfoByID GetChannelInfoByID;

typedef int (WINAPI *TtsrGetChannelInfoByName)(char *ChannelName,
                                   ChannelInfo *tsrChannelInfo,
                                   PlayerInfo *tsrPlayerInfo,
                                   int *PlayerRecords);
extern TtsrGetChannelInfoByName GetChannelInfoByName;

typedef int (WINAPI *TtsrGetPlayerInfoByID)(int PlayerID, PlayerInfo *tsrPlayerInfo);
extern TtsrGetPlayerInfoByID GetPlayerInfoByID;

typedef int (WINAPI *TtsrGetPlayerInfoByName)(char *PlayerName, PlayerInfo *tsrPlayerInfo);
extern TtsrGetPlayerInfoByName GetPlayerInfoByName;

typedef int (WINAPI *TtsrGetChannels)(ChannelInfo *tsrChannels, int *ChannelRecords);
extern TtsrGetChannels GetChannels;

typedef int (WINAPI *TtsrGetPlayers)(PlayerInfo *tsrPlayers, int PlayerRecords);
extern TtsrGetPlayers GetPlayers;

typedef int (WINAPI *TtsrGetSpeakers)(int *tsrPlayerIDs, int *PlayerRecords);
extern TtsrGetSpeakers GetSpeakers;

typedef int (WINAPI *TtsrSetPlayerFlags)(int tsrPlayerFlags);
extern TtsrSetPlayerFlags SetPlayerFlags;

typedef int (WINAPI *TtsrSetWantVoiceReason)(char *tsrReason);
extern TtsrSetWantVoiceReason SetWantVoiceReason;

typedef int (WINAPI *TtsrSetOperator)(int PlayerID, int GrantRevoke);
extern TtsrSetOperator SetOperator;

typedef int (WINAPI *TtsrSetVoice)(int PlayerID, int GrantRevoke);
extern TtsrSetVoice SetVoice;

typedef int (WINAPI *TtsrKickPlayerFromServer)(int PlayerID, char *reason);
extern TtsrKickPlayerFromServer KickPlayerFromServer;

typedef int (WINAPI *TtsrKickPlayerFromChannel)(int PlayerID, char *reason);
extern TtsrKickPlayerFromChannel KickPlayerFromChannel;

typedef int (WINAPI *TtsrSendTextMessageToChannel)(int ChannelID, char *Message);
extern TtsrSendTextMessageToChannel SendTextMessageToChannel;

typedef int (WINAPI *TtsrSendTextMessage)(char *Message);
extern TtsrSendTextMessage SendTextMessage;

extern HMODULE g_handle;

int InitTsRemoteLibrary(const char *LibName);

int CloseTsRemoteLibrary();


}