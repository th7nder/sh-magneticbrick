//
//  GlidingRotatingExtra.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 11/07/2017.
//
//

#include "GlidingRotatingExtra.hpp"


GlidingRotatingExtra::GlidingRotatingExtra()
{
    
}

GlidingRotatingExtra::~GlidingRotatingExtra()
{
    
}

GlidingRotatingExtra* GlidingRotatingExtra::create(GameHandler* handler)
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



bool GlidingRotatingExtra::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void GlidingRotatingExtra::launch()
{
    sprite->runAction(Spawn::create(RotateBy::create(6.0, 360), MoveBy::create(6.0, Vec2(orientation == "right" ? -640 : 640, 0)), NULL));
}
