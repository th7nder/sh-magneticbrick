//
//  FlyingExtra.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#include "FlyingExtra.hpp"

FlyingExtra::FlyingExtra()
{
    
}

FlyingExtra::~FlyingExtra()
{
    
}

FlyingExtra* FlyingExtra::create(GameHandler* handler)
{
    self* ret = new (std::nothrow) self();
    if (ret && ret->init(handler))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}



bool FlyingExtra::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void FlyingExtra::launch()
{
    sprite->runAction(MoveBy::create(10.0, Vec2(40, -1136)));
}

