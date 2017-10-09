//
//  SideExtra.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 20/06/2017.
//
//

#include "SideExtra.hpp"


SideExtra::SideExtra()
{
    
}

SideExtra::~SideExtra()
{
    
}

SideExtra* SideExtra::create(GameHandler* handler)
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

void SideExtra::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
    startX = props["x"].asFloat() / 1080.0 * 640;
    startX += width / 2;
    startY = props["y"].asFloat() / 1080.0 * 1136; 
    startY += height / 2;
    setPosition(Vec2(startX, startY));
    orientation = props["orientation"].asString();
}


bool SideExtra::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    
    setCascadeOpacityEnabled(true);
    setOpacity(120);
    return true;
}




void SideExtra::initPhysics(b2World *world)
{
    
}
