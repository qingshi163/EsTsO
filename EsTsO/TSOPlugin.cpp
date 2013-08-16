#include "StdAfx.h"
#include "TSOPlugin.h"
#include "TSOScreen.h"
#include "tsremote.h"

TSOPlugin::TSOPlugin(void)
    : CPlugIn(COMPATIBILITY_CODE, PLUGIN_NAME, PLUGIN_VERSION, PLUGIN_AUTHOR, PLUGIN_COPYRIGHT),
      is_tsremote_ok(false)
{
    LoadTsRemote();
}


TSOPlugin::~TSOPlugin(void)
{
    /* IMPORTANT! ES maybe will delete screen it self, so check screen before delete it. */
    if (g_screen)
        delete g_screen;
    g_screen = NULL;

    UnloadTsRemote();
}

CRadarScreen* TSOPlugin::OnRadarScreenCreated(const char *display_name,
                                              bool need_radar_content,
                                              bool geo_referenced,
                                              bool can_be_saved,
                                              bool can_be_created)
{
    if (is_tsremote_ok && strcmp(display_name, SCREEN_NAME) == 0)
    {
        g_screen = new TSOScreen;
        g_screen->SetShow(true);
        return g_screen;
    }
    return NULL;
}

bool TSOPlugin::OnCompileCommand(const char *commandline)
{
    const char *ci = commandline;

    if (strncmp(ci, ".tso", 4) != 0)
        return false;

    if (is_tsremote_ok)
        UnloadTsRemote();
    LoadTsRemote();

    if (g_screen)
    {
        g_screen->SetShow(!g_screen->IsShow());
    }

    return true;
}


void TSOPlugin::LoadTsRemote()
{
    if (!is_tsremote_ok)
    {
        if(!(is_tsremote_ok = !TSRemote::InitTsRemoteLibrary(TSREMOTE_DLL_NAME)))
        {
            MessageBox(NULL, "Failed to Load TSRemote.dll.", "TSO Failed", MB_OK);
        }
    }
}

void TSOPlugin::UnloadTsRemote()
{
    if (is_tsremote_ok)
    {
        TSRemote::CloseTsRemoteLibrary();
        is_tsremote_ok = false;
    }
}