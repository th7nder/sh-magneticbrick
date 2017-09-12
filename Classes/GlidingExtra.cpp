//
//  GlidingExtra.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#include "GlidingExtra.hpp"

GlidingExtra::GlidingExtra()
{
    
}

GlidingExtra::~GlidingExtra()
{
    
}

GlidingExtra* GlidingExtra::create(GameHandler* handler)
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



bool GlidingExtra::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void GlidingExtra::launch()
{
    sprite->runAction(Spawn::create(MoveBy::create(10.0, Vec2(orientation == "right" ? -640 : 640, 0)), NULL));
}
