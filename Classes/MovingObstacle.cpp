
//
//  MovingObstacle.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 15/03/2017.
//
//

#include "MovingObstacle.hpp"

MovingObstacle::MovingObstacle() : velocity(0), stopX(0)
{
    
}

MovingObstacle::~MovingObstacle()
{
    
}

MovingObstacle* MovingObstacle::create(GameHandler* handler)
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


bool MovingObstacle::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}

void MovingObstacle::setProperties(ValueMap &props)
{
    super::setProperties(props);
    
    
    CCASSERT(!props["stopX"].isNull(), "MovingObstacle stopX not set!");
    CCASSERT(!props["velocity"].isNull(), "MovingObstacle velocity not set!");
    stopX = (props["stopX"].asFloat()) / 1080.0 * 640;
    stopX += width / 2;
    auto v = props["velocity"].asFloat();
    velocity = pixelsToMeters(v);
    

}


void MovingObstacle::initPhysics(b2World *world)
{
    super::initPhysics(world);
    body->SetType(b2_kinematicBody);
}

void MovingObstacle::launch()
{
    body->SetLinearVelocity(b2Vec2(stopX > startX ? velocity : -velocity, 0));
}

void MovingObstacle::savePreviousStates()
{
    previousPosition = Vec2(body->GetPosition().x, body->GetPosition().y);
    
    float currentX = metersToPixels(body->GetPosition().x);
    //setPositionX(currentX);
    
    //CCLOG("currentX: %f stopX: %f", targetX, stopX);
    if(startX < stopX)
    {
        if(currentX >= stopX)
        {
            body->SetLinearVelocity(b2Vec2(-velocity, 0));
        } else if(currentX < startX)
        {
            body->SetLinearVelocity(b2Vec2(velocity, 0));
        }
    } else
    {
        if(currentX <= stopX)
        {
            body->SetLinearVelocity(b2Vec2(velocity, 0));
        }
        else if(currentX > startX)
        {
            body->SetLinearVelocity(b2Vec2(-velocity, 0));
        }
        
    }
}

void MovingObstacle::interpolate(float alpha)
{
    Vec2 target(metersToPixels(lerp(previousPosition.x, body->GetPosition().x, alpha)), metersToPixels(lerp(previousPosition.y, body->GetPosition().y, alpha)));
    setPosition(target);
}
