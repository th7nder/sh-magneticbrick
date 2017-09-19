
//
//  MovingObstacle.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 15/03/2017.
//
//

#include "MovingObstacle.hpp"

USING_NS_CC;

std::string MovingObstacle::leftTexture = "";
std::string MovingObstacle::centerTexture = "";
std::string MovingObstacle::rightTexture = "";

MovingObstacle::MovingObstacle() : velocity(0), stopX(0)
{
    
}

MovingObstacle::~MovingObstacle()
{
    
}


int MovingObstacle::getZ() const
{
    return 4;
}

void MovingObstacle::setProperties(ValueMap &props)
{
    super::setProperties(props);
    CCASSERT(!props["stopX"].isNull(), "MovingObstacle -> stopX isNull");
    CCASSERT(!props["velocity"].isNull(), "MovingObstacle -> velocity isNull");
    
    stopX = (props["stopX"].asFloat()) / 1080.0 * 640; // stopX not parsed by cocos
    stopX += _contentSize.width / 2;
    
    velocity = pixelsToMeters(props["velocity"].asFloat());
}


void MovingObstacle::addSprite()
{
    Sprite* spr = Sprite::create(leftTexture);
    spr->setAnchorPoint(Vec2::ZERO);
    addChild(spr);
    
    auto width = spr->getContentSize().width;
    auto height = spr->getContentSize().height;
    float fAmount = getContentSize().width / width;
    int amount = getContentSize().width / width;
    if(fAmount - amount > 0.5)
    {
        amount++;
    }
    if(amount > 2)
    {
        spr = Sprite::create(centerTexture);
        spr->setAnchorPoint(Vec2::ZERO);
        spr->setPosition(Vec2(width, 0));
        spr->setContentSize(Size((amount - 2) * width, height));
        addChild(spr);
    }
    

    spr = Sprite::create(rightTexture);
    
    spr->setAnchorPoint(Vec2::ZERO);
    spr->setPositionX(width + ((amount - 2) * width));
    addChild(spr);
}

void MovingObstacle::initPhysics(b2World *world)
{
    super::initPhysics(world);
    body->SetType(b2_kinematicBody);
}

void MovingObstacle::launch()
{
    body->SetLinearVelocity(b2Vec2(stopX > startPosition.x ? velocity : -velocity, 0));
}


// sth is reduntant here
void MovingObstacle::savePreviousStates()
{
    super::savePreviousStates();
    
    float currentX = getPositionX();
    if(startPosition.x < stopX)
    {
        if(currentX >= stopX)
        {
            body->SetLinearVelocity(b2Vec2(-velocity, 0));
        } else if(currentX < startPosition.x)
        {
            body->SetLinearVelocity(b2Vec2(velocity, 0));
        }
    } else
    {
        if(currentX <= stopX)
        {
            body->SetLinearVelocity(b2Vec2(velocity, 0));
        }
        else if(currentX > startPosition.x)
        {
            body->SetLinearVelocity(b2Vec2(-velocity, 0));
        }
        
    }
}
