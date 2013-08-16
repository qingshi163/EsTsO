#pragma once
#include "tsremote.h"

struct TSODataItem
{
    char nickname[30];
    bool is_speaking;
    bool is_commander;
};


class TSOData
{
private:
    bool ts_connected;
    TSODataItem *items;
    int count;
    bool changed;

    CCriticalSection lock;

    static TSOData *instance;

    friend class MTHelper;

public:

    class MTHelper
    {
    private:
        static TSOData& data;

    public:
        MTHelper(bool is_lock=true);
        ~MTHelper();

        bool Lock(int timeout=INFINITE);
        bool Unlock();

        const TSODataItem& operator[] (int index) const;

        TSOData& operator* ();
        const TSOData& operator* () const;
        TSOData* operator-> ();
        const TSOData* operator-> () const;
    };

    TSOData();
    ~TSOData();

    bool Update(TSRemote::PlayerInfo *players, int player_records, int *speaker_ids, int speaker_records);

    bool IsConnected() const;

    void Disconnect();

    bool IsChanged() const;

    bool ImplementChange();

    int Count() const;

    /* Return: true for completed copy. false for space not enougth, some items not copy */
    bool GetItems(TSODataItem *out_items, int& inout_records);

    const TSODataItem& operator[] (int index) const;

    static TSOData& GetInstance();
};

#include "TSOData-inl.h"