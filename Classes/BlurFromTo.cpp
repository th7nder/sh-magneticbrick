//
//  BlurFromTo.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 08/06/2017.
//
//

#include "BlurFromTo.hpp"
USING_NS_CC;

BlurFromTo* BlurFromTo::create(float duration, float fromValue, float toValue)
{
    BlurFromTo *BlurFromTo = new (std::nothrow) class BlurFromTo();
    if (BlurFromTo && BlurFromTo->initWithDuration(duration, fromValue, toValue)) {
        BlurFromTo->autorelease();
        return BlurFromTo;
    }
    
    delete BlurFromTo;
    return nullptr;
}

bool BlurFromTo::initWithDuration(float duration, float fromValue, float toValue)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _to = toValue;
        _from = fromValue;
        
        return true;
    }
    
    return false;
}

BlurFromTo* BlurFromTo::clone() const
{
    return BlurFromTo::create(_duration, _from, _to);
}


BlurFromTo* BlurFromTo::reverse() const
{
    return BlurFromTo::create(_duration, _to, _from);
}

void BlurFromTo::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
}

void BlurFromTo::update(float time)
{
    ((kBlurFromToCast)(_target))->setBlurRadius(_from + (_to - _from) * time);
}

