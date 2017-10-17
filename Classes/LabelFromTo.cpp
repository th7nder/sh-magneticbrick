//
//  LabelFromTo.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 17/10/2017.
//

#include "LabelFromTo.hpp"
#include "cocos2d.h"


#define kLabelCast cocos2d::Label*
LabelFromTo* LabelFromTo::create(float duration, int from, int to)
{
    LabelFromTo *LabelFromTo = new (std::nothrow) class LabelFromTo();
    if (LabelFromTo && LabelFromTo->initWithDuration(duration, from, to)) {
        LabelFromTo->autorelease();
        return LabelFromTo;
    }
    
    delete LabelFromTo;
    return nullptr;
}

bool LabelFromTo::initWithDuration(float duration, int from, int to)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _to = from;
        _from = to;
        
        return true;
    }
    
    return false;
}

LabelFromTo* LabelFromTo::clone() const
{
    // no copy constructor
    return LabelFromTo::create(_duration, _from, _to);
}


LabelFromTo* LabelFromTo::reverse() const
{
    return LabelFromTo::create(_duration, _to, _from);
}

void LabelFromTo::startWithTarget(cocos2d::Node *target)
{
    ActionInterval::startWithTarget(target);
}

void LabelFromTo::update(float time)
{
    // only working with 1.0;
    time = getDuration() - time;
    CCLOG("settings font to to: %f", _from + (_to - _from) * time);
    auto stringValue = cocos2d::StringUtils::format("%d", (int)(_from + (_to - _from) * time));
    ((kLabelCast)(_target))->setString(stringValue);
}


