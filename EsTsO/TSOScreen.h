#pragma once
#include <EuroScopePlugIn.h>
using namespace EuroScopePlugIn;
#include "tsremote.h"
#include "TSOView.h"

#define LIST_MAX_LENGTH 30
#define BG_THREAD_FREQUENCY 16

class TSOScreen;


extern TSOScreen *g_screen;
extern volatile int close_bg_thread_signal;
extern volatile CWinThread *bg_thread;

bool tsremote_is_connected();
UINT bg_thread_func(LPVOID pParam);


class TSOScreen : public CRadarScreen
{
private:
    TSOView view;
    bool is_show;

public:
    TSOScreen(void);
    virtual ~TSOScreen(void);

    void OnRefresh(HDC hdc, int phase);

    void OnMoveScreenObject(int type, const char *id, POINT point, RECT area, bool released)
    {
        view.OnMove(type, id, point, area, released);
    }

    void OnAsrContentLoaded(bool loaded);

    void OnAsrContentToBeSaved();

    void OnAsrContentToBeClosed()
    {
        delete this;
    }

    bool IsShow() const
    {
        return is_show;
    }

    void SetShow(bool is_show);
};

