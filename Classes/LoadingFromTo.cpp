//
//  LoadingFromTo.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 17/10/2017.
//

#include "LoadingFromTo.hpp"
#include "cocos2d.h"
#include "ui/UILoadingBar.h"


#define kLoadingBarCast cocos2d::ui::LoadingBar*

LoadingFromTo* LoadingFromTo::create(float duration, float fromPercentage, float toPercentage)
{
    LoadingFromTo *LoadingFromTo = new (std::nothrow) class LoadingFromTo();
    if (LoadingFromTo && LoadingFromTo->initWithDuration(duration, fromPercentage, toPercentage)) {
        LoadingFromTo->autorelease();
        return LoadingFromTo;
    }
    
    delete LoadingFromTo;
    return nullptr;
}

bool LoadingFromTo::initWithDuration(float duration, float fromPercentage, float toPercentage)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _to = toPercentage;
        _from = fromPercentage;
        
        return true;
    }
    
    return false;
}

LoadingFromTo* LoadingFromTo::clone() const
{
    // no copy constructor
    return LoadingFromTo::create(_duration, _from, _to);
}


LoadingFromTo* LoadingFromTo::reverse() const
{
    return LoadingFromTo::create(_duration, _to, _from);
}

void LoadingFromTo::startWithTarget(cocos2d::Node *target)
{
    ActionInterval::startWithTarget(target);
}

void LoadingFromTo::update(float time)
{
    CCLOG("settings percentage to: %f", _from + (_to - _from) * time);
    ((kLoadingBarCast)(_target))->setPercent(_from + (_to - _from) * time);
}

