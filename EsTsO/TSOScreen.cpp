#include "StdAfx.h"
#include "TSOScreen.h"

TSOScreen *g_screen = NULL;
volatile int close_bg_thread_signal = 0;
volatile CWinThread *bg_thread = NULL;

TSOScreen::TSOScreen(void)
    : view(*this),
      is_show(false)
{
}


TSOScreen::~TSOScreen(void)
{
    // Wait tsremote thread end.
    if (is_show)
    {
        SetShow(false);
    }
    g_screen = NULL;
}

void TSOScreen::OnRefresh(HDC hdc, int phase)
{
    if (!is_show)
        return;
    if (phase != REFRESH_PHASE_BEFORE_TAGS)
        return;


    // Draw View
    CDC dc;
    dc.Attach(hdc);
    view.OnRefresh(dc);
    dc.Detach();
    
    // background thread
    bool is_connected;
    {
    TSOData::MTHelper data;
    is_connected = data->IsConnected();
    }
    if (!is_connected)
    {
        if (tsremote_is_connected())
        {
            if (bg_thread == NULL)
                bg_thread = AfxBeginThread(bg_thread_func, NULL);
        }
    }

    // Draw background
    // ---------------

    /*EnterCriticalSection(g_data_lock);
    
    LOGFONT lf;
    //memset(&lf, 0, sizeof(LOGFONT));
    if (title_font == NULL)
    {
        dc.GetCurrentFont()->GetLogFont(&lf);
        lf.lfHeight = 14;
        title_font = new CFont;
        title_font->CreateFontIndirect(&lf);
    }
    if (nickname_font == NULL)
    {
        lf.lfHeight = 16;
        nickname_font = new CFont;
        nickname_font->CreateFontIndirect(&lf);
    }

    if (!g_data.ts_connected)
    {
        if (tso_check_tsremote_is_connected())
        {
            g_data.ts_connected = true;

            g_thread = AfxBeginThread(tso_check_tsremote_thread, NULL);
        }

        dc.SetTextColor(title_color);

        
        dc.SelectObject(title_font);
        dc.TextOut(position.x, position.y, "TS Disconnect");
    }
    else
    {
        
        dc.SetTextColor(title_color);
        dc.SelectObject(title_font);
        dc.TextOut(position.x, position.y, "TS Connected");
        dc.SelectObject(nickname_font);
        for (int i = 0; i < TSO_LIST_LENGTH; i++)
        {
            if (g_data.item[i].is_showing)
            {
                if (g_data.item[i].is_speaking)
                    dc.SetTextColor(active_color);
                else
                    dc.SetTextColor(inactive_color);
                dc.TextOut(position.x + 20, position.y + 20 + i * 16, g_data.item[i].nickname);
            }
        }
    }

    LeaveCriticalSection(g_data_lock);*/

    //dc.Detach();
}

bool tsremote_is_connected()
{
    // TODO:
    //TSRemote::Version ts_version;
    //TSRemote::GetVersion(&ts_version);
    //return ts_version.Major == 2;

    TSRemote::UserInfo user_info;
    return !TSRemote::GetUserInfo(&user_info);
}

UINT bg_thread_func(LPVOID lParam)
{
    TSRemote::UserInfo user_info;
    TSRemote::ChannelInfo channel_info;
    TSRemote::PlayerInfo players[LIST_MAX_LENGTH];
    int speaker_ids[LIST_MAX_LENGTH];
    int player_records;
    int speaker_records;

    while (true)
    {
        // atomic signal
        if (close_bg_thread_signal)
        {
            TSOData::MTHelper data;
            data->Disconnect();
            close_bg_thread_signal = 0;
            bg_thread = NULL;
            return 0;
        }

        // Check players
        player_records = LIST_MAX_LENGTH;
        speaker_records = LIST_MAX_LENGTH;

        if (TSRemote::GetUserInfo(&user_info) ||
            TSRemote::GetChannelInfoByID(user_info.Player.ChannelID, &channel_info, players, &player_records) ||
            TSRemote::GetSpeakers(speaker_ids, &speaker_records))
        {
            // ts disconnect or error. exit
            TSOData::MTHelper data;
            data->Disconnect();
            bg_thread = NULL;
            return -1;
        }

        // Update data
        bool data_changed;
        {
        TSOData::MTHelper data;
        data_changed = data->Update(players, player_records, speaker_ids, speaker_records);
        }
        if (data_changed)
        {
            // TODO: don't sure this function is multi-thread safed.
            g_screen->RequestRefresh();
        }

        // Sleep
        Sleep(BG_THREAD_FREQUENCY);
    }
}


void TSOScreen::OnAsrContentLoaded(bool loaded)
{
    if (loaded)
        view.OnLoadSettings();
}

void TSOScreen::OnAsrContentToBeSaved()
{
    view.OnSaveSettings();
}

void TSOScreen::SetShow(bool is_show_)
{
    if (is_show && !is_show_)
    {
        // Close
        if (bg_thread)
        {
            close_bg_thread_signal = 1;
            WaitForSingleObject(bg_thread->m_hThread, INFINITE);
        }
    }

    if (is_show != is_show_)
    {
        is_show = is_show_;
        RequestRefresh();
    }
}