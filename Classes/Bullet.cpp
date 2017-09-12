//
//  Bullet.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 01/06/2017.
//
//

#include "Bullet.hpp"

Bullet::Bullet()
{
    
}

Bullet::~Bullet()
{
    
}

Bullet* Bullet::create(GameHandler* handler)
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


bool Bullet::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void Bullet::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
    velocity.x = pixelsToMeters(props["vX"].asFloat());
    velocity.y = pixelsToMeters(props["vY"].asFloat());
    angle = CC_RADIANS_TO_DEGREES(atanf(velocity.x / velocity.y));
}


void Bullet::addSprite()
{
    sprite = cocos2d::Sprite::create(Globals::resources["obstacle_bullet"]);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
    sprite->setRotation(angle);
}

void Bullet::launch()
{
    body->SetLinearVelocity(velocity);
}



void Bullet::initPhysics(b2World *world)
{
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPositionX(), getPositionY()));
    body->CreateFixture(createFixture(createRectangularShape(size.width, size.height)));
    
    body->SetType(b2_kinematicBody);

    body->SetTransform(body->GetPosition(), CC_DEGREES_TO_RADIANS(180.0f - angle));
    

}

void Bullet::savePreviousStates()
{
    previousPosition = Vec2(body->GetPosition().x, body->GetPosition().y);
    
    //float targetX = metersToPixels(body->GetPosition().x);
    //float targetY = metersToPixels(body->GetPosition().y);
    //setPosition(targetX, targetY);
}

void Bullet::interpolate(float alpha)
{
    Vec2 target(metersToPixels(lerp(previousPosition.x, body->GetPosition().x, alpha)), metersToPixels(lerp(previousPosition.y, body->GetPosition().y, alpha)));
    setPosition(target);
}
