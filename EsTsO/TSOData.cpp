#include "StdAfx.h"
#include "TSOData.h"


TSOData *TSOData::instance = new TSOData;
TSOData& TSOData::MTHelper::data = TSOData::GetInstance();

TSOData::TSOData()
    : ts_connected(false),
      items(NULL),
      count(0),
      changed(1)
{
}

TSOData::~TSOData()
{
    if (items)
        delete items;
}

bool TSOData::Update(TSRemote::PlayerInfo *players, int player_records, int *speaker_ids, int speaker_records)
{
    TSODataItem *new_items;

    new_items = player_records > 0 ? new TSODataItem[player_records] : NULL;

    int i, j;
    for (i = 0; i < player_records; i++)
    {
        strcpy_s(new_items[i].nickname, players[i].NickName);
        new_items[i].is_commander = players[i].PlayerFlags & TSRemote::PlayerFlags::ChannelCommander;

        // check if speaking
        for (j = 0; j < speaker_records; j++)
        {
            if (players[i].PlayerID == speaker_ids[j])
            {
                new_items[i].is_speaking = true;
                break;
            }
        }
        // not the speaker
        if (j == speaker_records)
        {
            new_items[i].is_speaking = false;
        }
    }

    // same value
    if (count == player_records &&
        (player_records == 0 || memcmp(items, new_items, sizeof(TSODataItem) * player_records) == 0))
    {
        changed = false;
        if (new_items)
            delete new_items;
        // new_items = NULL;
    }
    // new value, update data
    else
    {
        changed = true;
        if (items)
            delete items;
        items = new_items;
        count = player_records;
    }

    if (!ts_connected)
    {
        ts_connected = true;
        changed = true;
    }

    return changed;
}



void TSOData::Disconnect()
{
    if (ts_connected)
    {
        // make clean
        ts_connected = false;
        changed = true;
        count = 0;
        if (items)
        {
            delete items;
            items = NULL;
        }
    }
}

bool TSOData::ImplementChange()
{
    if (changed)
    {
        changed = false;
        return true;
    }
    return false;
}

bool TSOData::GetItems(TSODataItem *out_items, int& inout_records)
{
    if (!ts_connected || count == 0)
    {
        inout_records = 0;
        return true;
    }

    bool is_enougth = (inout_records >= count);

    memcpy(out_items, items, sizeof(TSODataItem) * (is_enougth ? count : inout_records));

    return is_enougth;
}


TSOData::MTHelper::MTHelper(bool is_lock)
{
    if (is_lock)
        data.lock.Lock();
}

TSOData::MTHelper::~MTHelper()
{
    data.lock.Unlock();
}