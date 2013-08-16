#pragma once

template<typename V>
TSOProperty<V>::TSOProperty(TSOScreen& screen_, const char *name_, const V& default_value_, const char *description_)
    : screen(screen_), name(name_), value(default_value_), description(description_)
{
}


template<typename V>
TSOProperty<V>::~TSOProperty(void)
{
}

template<typename V>
inline V& TSOProperty<V>::operator() ()
{
    return value;
}

template<typename V>
inline const V& TSOProperty<V>::operator() () const
{
    return value;
}