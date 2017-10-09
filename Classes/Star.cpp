//
//  Star.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 09/03/2017.
//
//

#include "Star.hpp"
#include "Level.hpp"


Star::Star() : number(0)
{
  
}

Star::~Star()
{
    
}

Star* Star::create(GameHandler* handler)
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


bool Star::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void Star::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
    CCASSERT(!props["name"].isNull(), "initialSpeed was not set in map!");
    number = props["name"].asInt();
    if(gameHandler->getStar(number)) remove = true;
    
    gameHandler->addStarBar(getPositionY(), remove);
}


void Star::addSprite()
{
    if(remove) return;
    //" + gameHandler->getLastTheme().getElementsColor()
    
    sprite = cocos2d::Sprite::create(Globals::resources["icon_star_collect_white"]);
    sprite->setColor(Color3B(255, 215, 0));
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setCascadeOpacityEnabled(true);
    auto seq = Sequence::create(FadeTo::create(0.5, 10), FadeIn::create(0.3), DelayTime::create(0.4), NULL);
    sprite->runAction(RepeatForever::create(seq));
    addChild(sprite);
}

bool Star::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    return false;
}

void Star::initPhysics(b2World *world)
{
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPositionX(), getPositionY()));
    auto fixture = createFixture(createRectangularShape(size.width, size.height));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}
