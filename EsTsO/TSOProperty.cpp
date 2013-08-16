#include "StdAfx.h"
#include "TSOProperty.h"
#include "TSOScreen.h"



IntProperty::IntProperty(TSOScreen& screen_, const char *name_, const int& default_value_, const char *description_)
    : TSOProperty<int>(screen_, name_, default_value_, description_)
{
}

bool IntProperty::Load()
{
    const char *tmp;
    if (tmp = screen.GetDataFromAsr(name))
    {
        value = atoi(tmp);
        return true;
    }
    return false;
}

void IntProperty::Save()
{
    char tmp[32];
    sprintf_s(tmp, "%d", value);
    screen.SaveDataToAsr(name, description, tmp);
}

ColorProperty::ColorProperty(TSOScreen& screen_, const char *name_, const COLORREF& default_value_, const char *description_)
    : TSOProperty<COLORREF>(screen_, name_, default_value_, description_)
{
}

bool ColorProperty::Load()
{
    int r,g,b;
    const char *tmp;
    if (tmp = screen.GetDataFromAsr(name))
    {
        sscanf_s(tmp, "#%2X%2X%2X", &r, &g, &b);
        value = RGB(r,g,b);
        return true;
    }
    return false;
}

void ColorProperty::Save()
{
    char tmp[8];
    sprintf_s(tmp, "#%02X%02X%02X", GetRValue(value), GetGValue(value), GetBValue(value));
    screen.SaveDataToAsr(name, description, tmp);
}