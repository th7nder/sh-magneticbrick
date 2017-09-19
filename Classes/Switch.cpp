//
//  Switch.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 02/02/2017.
//
//

#include "Switch.hpp"
USING_NS_CC;
Switch::Switch() : side(Side::NotSet), button(nullptr), buttonBody(nullptr), target(""), underBody(nullptr)
{
    
}

Switch::~Switch()
{
    buttonBody->GetWorld()->DestroyBody(buttonBody);
    underBody->GetWorld()->DestroyBody(underBody);
}

void Switch::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
    CCASSERT(!props["target"].isNull(), "Switch without target!");
    side = props["side"].asString() == "right" ? Side::Right : Side::Left;
    target = props["target"].asString();
}

void Switch::addSprite()
{
    sprite = Sprite::create(Globals::resources["obstacle_switch_red"]);
    sprite->setAnchorPoint(Vec2::ZERO);
    
    if(side == Side::Right)
    {
        button = Sprite::create(Globals::resources["obstacle_switch_right"]);
        button->setAnchorPoint(Vec2::ZERO);
        button->setPositionX(sprite->getContentSize().width);
        
    }
    else if(side == Side::Left)
    {
        button = Sprite::create(Globals::resources["obstacle_switch_left"]);
        button->setAnchorPoint(Vec2::ZERO);
        setPositionX(getPositionX() - button->getContentSize().width);
        sprite->setPositionX(button->getContentSize().width);
    }
    
    
    setContentSize(sprite->getContentSize());
    
    addChild(sprite);
    addChild(button);

}

b2Body* Switch::createUnderbody(b2World *world, float x, float y, float width)
{
  
    auto ret = world->CreateBody(createBody(Vec2(x, y)));
    auto shape = new b2EdgeShape;
    shape->Set(b2Vec2(-width / 2, 0), b2Vec2(width / 2, 0));
    ret->CreateFixture(createFixture(shape));
    
    return ret;
}

void Switch::initPhysics(b2World *world)
{

    body = world->CreateBody(createBody(Vec2(side == Side::Right ? getPositionX() : getPositionX() + _contentSize.width / 2, getPositionY())));
    body->CreateFixture(createFixture(createRectangularShape(_contentSize)));
    
    
    underBody = createUnderbody(world, side == Side::Right ? getPositionX() : getPositionX() + _contentSize.width / 2, getPositionY() - _contentSize.height / 2, pixelsToMeters(_contentSize.width - 10));
    
    
    buttonSize = button->getContentSize();
    buttonSize.width /= 3;
    buttonSize.height /= 2;

    b2Vec2 pos;
    if(side == Side::Right)
    {
        pos = b2Vec2(getPositionX() + _contentSize.width / 2 + buttonSize.width / 2, getPositionY());
    } else if(side == Side::Left){
        pos = b2Vec2(getPositionX() - buttonSize.width / 2, getPositionY());
    }
    
    
    auto bodyDef = createBody(Vec2(pos.x, pos.y));
    bodyDef->type = b2_dynamicBody;
    buttonBody = world->CreateBody(bodyDef);
    auto buttonFixture = createFixture(createRectangularShape(buttonSize));
    buttonFixture->isSensor = true;
    buttonFixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    buttonFixture->filter.maskBits = kFilterCategoryPlayer;
    buttonBody->CreateFixture(buttonFixture);
}

bool Switch::OnContactBegin(LevelObject *other, b2Body* otherBody)
{

    bool invisible = other->getOpacity() != 255;
    if(!invisible && otherBody == underBody)
    {
        return true;
    }
    
    float switchY = body->GetPosition().y - pixelsToMeters(_contentSize.height / 2);
    float brickY = other->getBody()->GetPosition().y + pixelsToMeters(other->getContentSize().height / 2);
    if(!invisible && brickY - switchY >= 0 && brickY - switchY <= 0.1f)
    {
        return true;
    }
    
    switchY = buttonBody->GetPosition().y - pixelsToMeters(buttonSize.height / 2);
    if(!invisible && brickY - switchY >= 0 && brickY - switchY <= 0.1f)
    {
        return true;
    }
    
    auto laserNode = getParent()->getChildByName(target);
    auto laser = dynamic_cast<Laser*>(laserNode);
    if(laser != nullptr)
    {
        sprite->setTexture(Globals::resources["obstacle_switch_green"]);
        laser->queueToRemove();
        auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
        std::string effect = StringUtils::format("effect_laseroff_%d", random(1, 3));
        sae->playEffect(Globals::resources[effect.c_str()].c_str());
    }
    
    return false;
}

