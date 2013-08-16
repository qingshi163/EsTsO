#pragma once
#include "TSOData.h"
#include "TSOProperty.h"

#define TITLE_NAME "ESTSO 1.2.0 alpha"

#define SIGNAL_TITLE 1

class TSOScreen;

class TSOView
{
private:

    ColorProperty title_color;
    ColorProperty text_color;
    ColorProperty active_color;
    ColorProperty inactive_color;
    IntProperty text_size;
    IntProperty title_size;
    IntProperty title_text_size;

    IntProperty position_x;
    IntProperty position_y;

    CBrush active_brush;
    CBrush inactive_brush;
    CPen active_pen;
    CPen inactive_pen;

    CPoint on_move_p1;
    bool on_move_pressing;

    TSOScreen& screen;

public:
    TSOView(TSOScreen& screen);
    ~TSOView(void);

    // TODO: Style control

    void OnLoadSettings();

    void OnSaveSettings();

    void OnRefresh(CDC& dc);

    void OnMove(int type, const char *id, POINT point, RECT area, bool released);
};

