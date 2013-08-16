#pragma once
#include "TSOData.h"

inline TSOData& TSOData::GetInstance()
{
    return *instance;
}

inline bool TSOData::IsConnected() const
{
    return ts_connected;
}

inline bool TSOData::IsChanged() const
{
    return changed;
}

inline int TSOData::Count() const
{
    return count;
}

inline const TSODataItem& TSOData::operator[] (int index) const
{
    ASSERT(ts_connected && count > 0 && index < count && index >= 0);

    return items[index];
}


inline bool TSOData::MTHelper::Lock(int timeout)
{
    return !!data.lock.Lock(timeout);
}

inline bool TSOData::MTHelper::Unlock()
{
    return !!data.lock.Unlock();
}

inline const TSODataItem& TSOData::MTHelper::operator[] (int index) const
{
    return data[index];
}

inline TSOData* TSOData::MTHelper::operator-> ()
{
    return &data;
}

inline const TSOData* TSOData::MTHelper::operator-> () const
{
    return &data;
}

inline TSOData& TSOData::MTHelper::operator* ()
{
    return data;
}

inline const TSOData& TSOData::MTHelper::operator* () const
{
    return data;
}