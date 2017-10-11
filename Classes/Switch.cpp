//
//  Switch.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 02/02/2017.
//
//

#include "Switch.hpp"
#include "Player.hpp"

Switch::Switch() : side(Side::NotSet), button(nullptr), buttonBody(nullptr), target(""), underBody(nullptr), intelGiver(false)
{
    
}

Switch::~Switch()
{
    buttonBody->GetWorld()->DestroyBody(buttonBody);
    underBody->GetWorld()->DestroyBody(underBody);
}

Switch* Switch::create(GameHandler* handler)
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


bool Switch::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void Switch::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
    CCASSERT(!props["target"].isNull(), "Switch without target!");
    side = props["side"].asString() == "right" ? Side::Right : Side::Left;
    target = props["target"].asString();
    
    if(getPositionX() < _director->getVisibleSize().width / 2)
    {
        intelGiver = true;
    }
    
    
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
  
    auto ret = world->CreateBody(createBody(x, y));
    auto shape = new b2EdgeShape;
    shape->Set(b2Vec2(-width / 2, 0), b2Vec2(width / 2, 0));
    ret->CreateFixture(createFixture(shape));
    
    return ret;
}

void Switch::initPhysics(b2World *world)
{
    auto contentSize = getContentSize();
    
    body = world->CreateBody(createBody(side == Side::Right ? getPositionX() : getPositionX() + contentSize.width / 2, getPositionY() + (contentSize.height / 4)));
    body->CreateFixture(createFixture(createRectangularShape(contentSize.width, contentSize.height + (contentSize.height / 2))));
    
    
    underBody = createUnderbody(world, side == Side::Right ? getPositionX() : getPositionX() + contentSize.width / 2, getPositionY() - contentSize.height / 2, pixelsToMeters(contentSize.width - 10));
    
    
    buttonSize = button->getContentSize();
    buttonSize.width /= 3;
    buttonSize.height /= 2;

    b2Vec2 pos;
    if(side == Side::Right)
    {
        pos = b2Vec2(getPositionX() + contentSize.width / 2 + buttonSize.width / 2, getPositionY());
    } else if(side == Side::Left){
        pos = b2Vec2(getPositionX() - buttonSize.width / 2, getPositionY());
    }
    
    auto bodyDef = createBody(pos.x, pos.y);
    bodyDef->type = b2_dynamicBody;
    buttonBody = world->CreateBody(bodyDef);
    auto buttonFixture = createFixture(createRectangularShape(buttonSize.width, buttonSize.height));
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
    
    float switchY = body->GetPosition().y - pixelsToMeters(height / 2);
    float brickY = other->getBody()->GetPosition().y + pixelsToMeters(other->height / 2);
    if(!invisible && brickY - switchY >= 0 && brickY - switchY <= 0.1f)
    {
        return true;
    }
    
    /*switchY = buttonBody->GetPosition().y - pixelsToMeters(buttonSize.height / 2);
    if(!invisible && brickY - switchY >= 0 && brickY - switchY <= 0.1f)
    {
        return true;
    }*/
    
    auto laserNode = getParent()->getChildByName(target);
    auto laser = dynamic_cast<Laser*>(laserNode);
    if(laser != nullptr)
    {
        sprite->setTexture(Globals::resources["obstacle_switch_green"]);
        laser->remove = true;
        auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
        std::string effect = StringUtils::format("effect_laseroff_%d", random(1, 3));
        sae->playEffect(Globals::resources[effect.c_str()].c_str());
    }
    
    if(intelGiver && otherBody == body)
    {
      //  CCLOG("giving intel");
        Player* player = dynamic_cast<Player*>(other);
        player->setNearSwitch(side);
    }
   
    
    return false;
}

bool Switch::OnContactEnd(LevelObject *other)
{
    if(!intelGiver) return false;
    
   // CCLOG("%d intelGivr %f %f", intelGiver, getPositionX(), _director->getVisibleSize().width / 2);
    
    float switchY = body->GetPosition().y + pixelsToMeters(_contentSize.height / 4);
    float playerY = other->getBody()->GetPosition().y;
    
    if(playerY >= switchY)
    {
        Player* player = dynamic_cast<Player*>(other);
        player->setNearSwitch(0);
    }
    
    
    
    return false;
}

