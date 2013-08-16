#include "StdAfx.h"
#include "TSOView.h"
#include "TSOScreen.h"


TSOView::TSOView(TSOScreen& screen_)
    : screen(screen_),
      title_color(screen_, "title color", RGB(200, 0, 0)),
      text_color(screen_, "text color", RGB(200, 200, 200)),
      active_color(screen_, "active color", RGB(100, 255, 100)),
      inactive_color(screen_, "inactive color", RGB(0, 150, 0)),
      text_size(screen_, "text size", 14),
      title_size(screen_, "title size", 20),
      title_text_size(screen_, "title text size", 16),
      position_x(screen_, "position x", 200),
      position_y(screen_, "position y", 200),
      on_move_pressing(false)
{
    active_brush.CreateSolidBrush(active_color());
    inactive_brush.CreateSolidBrush(inactive_color());
    active_pen.CreateStockObject(NULL_PEN);
    inactive_pen.CreateStockObject(NULL_PEN);
}


TSOView::~TSOView(void)
{
}

void TSOView::OnLoadSettings()
{
    title_color.Load();
    text_color.Load();
    active_color.Load();
    inactive_color.Load();
    text_size.Load();
    title_size.Load();
    title_text_size.Load();
    position_x.Load();
    position_y.Load();

    active_brush.CreateSolidBrush(active_color());
    inactive_brush.CreateSolidBrush(inactive_color());
    active_pen.CreateStockObject(NULL_PEN);
    inactive_pen.CreateStockObject(NULL_PEN);

}

void TSOView::OnSaveSettings()
{
    title_color.Save();
    text_color.Save();
    active_color.Save();
    inactive_color.Save();
    text_size.Save();
    title_size.Save();
    title_text_size.Save();
    position_x.Save();
    position_y.Save();
}


void TSOView::OnRefresh(CDC& dc)
{
    TSODataItem *items = NULL;
    int count;
    CRect title_rect;

    /* Get Items */
    {
    TSOData::MTHelper data;
    count = data->Count();
    if (count > 0)
    {
        items = new TSODataItem[count];
        data->GetItems(items, count);
    }
    data->ImplementChange();
    }

    /* Draw background */

    dc.SetTextColor(title_color());

    // get title rectangle
    dc.DrawText(TITLE_NAME, &title_rect, DT_CALCRECT);
    title_rect.OffsetRect(position_x() - 20, position_y() - 20);

    // show title
    dc.DrawText(TITLE_NAME, &title_rect, 0);

    /* Draw Items */

    dc.SetTextColor(text_color());

    for (int i = 0; i < count; i++)
    {
        const TSODataItem& item = items[i];
        int bx = position_x();
        int by = position_y() + i * text_size();

        if (item.is_speaking)
        {
            dc.SelectObject(&active_brush);
            dc.SelectObject(&active_pen);
        }
        else
        {
            dc.SelectObject(&inactive_brush);
            dc.SelectObject(&inactive_pen);
        }
        

        /* SetDCBrushColor don't work! */
        //dc.SetDCBrushColor(active_color);

        dc.Rectangle(bx, by, bx + text_size(), by + text_size());
        dc.TextOut(bx + text_size(), by, item.nickname);

    }

    /* Make Clean */
    if (items)
        delete items;

    /* Bind signal */
    screen.AddScreenObject(SIGNAL_TITLE, "tso:title", title_rect, true, "");
}

void TSOView::OnMove(int type, const char *id, POINT point, RECT area, bool released)
{
    switch (type)
    {
    case SIGNAL_TITLE:
    {
        CPoint& p1 = on_move_p1;
        CPoint& p2 = static_cast<CPoint>(point);
        int& px = position_x();
        int& py = position_y();
        if (!on_move_pressing && !released)
        {
            // First time
            p1 = p2;
            on_move_pressing = true;
            break;
        }
        if (on_move_pressing && !released)
        {
            // moving
            SIZE gap_size = p2 - p1;
            px += gap_size.cx;
            py += gap_size.cy;
            p1 = p2;

            screen.RequestRefresh();
            break;
        }
        if (on_move_pressing && released)
        {
            on_move_pressing = false;
            break;
        }
    }
    }
}