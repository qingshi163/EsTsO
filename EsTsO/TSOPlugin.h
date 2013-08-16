#pragma once
#include <EuroScopePlugIn.h>
using namespace EuroScopePlugIn;

#define PLUGIN_NAME       "EsTsO"
#define PLUGIN_VERSION    "1.2.0 alpha"
#define PLUGIN_AUTHOR     "Kangzhi Shi"
#define PLUGIN_COPYRIGHT  "Free to be distributed"
#define SCREEN_NAME       "Standard ES radar screen"
#define TSREMOTE_DLL_NAME "TSRemote.dll"

class TSOPlugin : public CPlugIn
{
private:
    bool is_tsremote_ok;

public:
    TSOPlugin(void);
    virtual ~TSOPlugin(void);

    void LoadTsRemote();

    void UnloadTsRemote();

    bool OnCompileCommand(const char *commmandline);

    CRadarScreen* OnRadarScreenCreated(const char *display_name,
                                       bool need_radar_content,
                                       bool geo_referenced,
                                       bool can_be_saved,
                                       bool can_be_created);
};

