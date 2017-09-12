//
//  FlyingRotatingExtra.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#include "FlyingRotatingExtra.hpp"


FlyingRotatingExtra::FlyingRotatingExtra()
{
    
}

FlyingRotatingExtra::~FlyingRotatingExtra()
{
    
}

FlyingRotatingExtra* FlyingRotatingExtra::create(GameHandler* handler)
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



bool FlyingRotatingExtra::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void FlyingRotatingExtra::launch()
{
    sprite->runAction(Spawn::create(RotateBy::create(10.0, 360), MoveBy::create(10.0, Vec2(40, -1136)), NULL));
}
