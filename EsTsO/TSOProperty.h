#pragma once

class TSOScreen;

template<typename V>
class TSOProperty
{
protected:
    const char *name;
    const char *description;
    V value;

    TSOScreen& screen;

public:
    TSOProperty(TSOScreen& screen, const char *name, const V& default_value, const char *description="");
    virtual ~TSOProperty(void);

    virtual bool Load() = 0;
    virtual void Save() = 0;

    V& operator() ();
    const V& operator() () const;
};


class IntProperty : public TSOProperty<int>
{
public:
    IntProperty(TSOScreen& screen, const char *name, const int& default_value, const char *description="");
    bool Load();
    void Save();
};


class ColorProperty : public TSOProperty<COLORREF>
{
public:
    ColorProperty(TSOScreen& screen, const char *name, const COLORREF& default_value, const char *description="");
    bool Load();
    void Save();
};

#include "TSOProperty-inl.h"