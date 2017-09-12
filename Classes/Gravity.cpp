//
//  Gravity.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 13/06/2017.
//
//

#include "Gravity.hpp"

#include "Level.hpp"

Gravity::Gravity()
{
    
}

Gravity::~Gravity()
{
    
}

Gravity* Gravity::create(GameHandler* handler)
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


bool Gravity::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


bool Gravity::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    gameHandler->setGravity(true);
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->playEffect(Globals::resources["effect_gravity"].c_str());
    ((Level*)getParent())->updatePlayerPos();
    return false;
}

void Gravity::addSprite()
{
    const std::string downTexture = "obstacles/gravity_left_down.png";
    const std::string centerTexture = "obstacles/gravity_left_mid.png";
    const std::string upTexture = "obstacles/gravity_left_up.png";
    
    auto spr = Sprite::create(downTexture);
    spr->setAnchorPoint(Vec2::ZERO);
    addChild(spr);
    
    auto height = spr->getContentSize().height;
    float fAmount = getContentSize().height / height;
    int amount = getContentSize().height / height;
    if(fAmount - amount > 0.5)
    {
        amount++;
    }
    if(amount > 1)
    {
        spr = Sprite::create(centerTexture);
        spr->setAnchorPoint(Vec2::ZERO);
        spr->setPosition(Vec2(0, height));
        spr->setContentSize(Size(spr->getContentSize().width, (amount - 1) * height));
        addChild(spr);
    }
    
    spr = Sprite::create(upTexture);
    spr->setAnchorPoint(Vec2::ZERO);
    spr->setPosition(Vec2(0, height + ((amount - 1) * height)));
    addChild(spr);
    
    
    const std::string downRightTexture = "obstacles/gravity_right_down.png";
    const std::string centerRightTexture = "obstacles/gravity_right_mid.png";
    const std::string upRightTexture = "obstacles/gravity_right_up.png";
    
    const float  x = ownVisibleSize.width - spr->getContentSize().width;
    spr = Sprite::create(downRightTexture);
    spr->setAnchorPoint(Vec2::ZERO);
    spr->setPositionX(x);
    addChild(spr);
    

    if(fAmount - amount > 0.5)
    {
        amount++;
    }
    if(amount > 1)
    {
        spr = Sprite::create(centerRightTexture);
        spr->setAnchorPoint(Vec2::ZERO);
        spr->setPosition(Vec2(x, height));
        spr->setContentSize(Size(spr->getContentSize().width, (amount - 1) * height));
        addChild(spr);
    }
    
    spr = Sprite::create(upRightTexture);
    spr->setAnchorPoint(Vec2::ZERO);
    spr->setPosition(Vec2(x, height + ((amount - 1) * height)));
    addChild(spr);
}


bool Gravity::OnContactEnd(LevelObject *other)
{
    gameHandler->setGravity(false);
    ((Level*)getParent())->updatePlayerPos();
    return false;
}



void Gravity::initPhysics(b2World *world)
{
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPositionX(), getPositionY()));
    auto fixture = createFixture(createRectangularShape(size.width, size.height));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}


