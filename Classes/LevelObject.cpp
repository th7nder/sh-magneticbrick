//
//  LevelObject.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 30/01/2017.
//
//


#include "LevelObject.hpp"
USING_NS_CC;

Size LevelObject::ownVisibleSize(0, 0);


LevelObject::LevelObject() : body(nullptr), sprite(nullptr), remove(false), gameHandler(nullptr), width(0.0), startX(0.0)
{
    
}

LevelObject::~LevelObject()
{
    if(body)
    {
        body->GetWorld()->DestroyBody(body);
    }

    gameHandler = nullptr;
    removeAllChildrenWithCleanup(true);
}

LevelObject* LevelObject::create(GameHandler* handler)
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

bool LevelObject::init(GameHandler *handler)
{
    if(!super::init())
    {
        return false;
    }
    gameHandler = handler;
    
    return true;
}


void LevelObject::setProperties(ValueMap &properties)
{
    auto scale =_director->getContentScaleFactor();
    CCASSERT(!properties["width"].isNull(), "h3h3h3");
    CCASSERT(!properties["height"].isNull(), "noniemozliwe");
    width = (properties["width"].asFloat() / 1080.0) * 640 * scale;
    height = (properties["height"].asFloat() / 1920.0) * 1136 * scale;
    
    startX = properties["x"].asFloat() / 1080.0 * 640 * scale;
    startX += width / 2;
    startY = properties["y"].asFloat() / 1920.0 * 1136 * scale;
    startY += height / 2;
    
    previousPosition = Vec2(pixelsToMeters(startX), pixelsToMeters(startY));
    this->setAnchorPoint(Vec2(0.5, 0.5));
    this->setPosition(Point(startX, startY));
    this->setContentSize(Size(width, height));
}

b2BodyDef* LevelObject::createBody(float x, float y)
{
    b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->type = b2_staticBody;
    bodyDef->position = b2Vec2(pixelsToMeters(x), pixelsToMeters(y));
    bodyDef->userData = this;
    bodyDef->fixedRotation = true;
    return bodyDef;
}

b2PolygonShape* LevelObject::createRectangularShape(float width, float height)
{
    b2PolygonShape* shape = new b2PolygonShape();
    shape->SetAsBox(pixelsToMeters(width / 2), pixelsToMeters(height / 2));
    return shape;
}

b2CircleShape* LevelObject::createCircleShape(float radius)
{
    b2CircleShape* shape = new b2CircleShape();
    shape->m_p.Set(pixelsToMeters(+radius), pixelsToMeters(+radius));
    shape->m_radius = pixelsToMeters(radius);
    return shape;
}


b2FixtureDef* LevelObject::createFixture(b2Shape *shape)
{
    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;
    fixtureDef->density = 1.0;
    fixtureDef->friction = 0.0;
    fixtureDef->restitution = 0.0;
    fixtureDef->filter.categoryBits = kFilterCategorySolidObject;
    fixtureDef->filter.maskBits = kFilterCategoryPlayer;
    
    return fixtureDef;
}

void LevelObject::initPhysics(b2World* world)
{
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPositionX(), getPositionY()));
    body->CreateFixture(createFixture(createRectangularShape(size.width, size.height)));
}

void LevelObject::scheduleRemove(float time)
{
    auto func = CallFunc::create([this](){
        this->remove = true;
    });
    

    auto seq = Sequence::create(DelayTime::create(time), func, NULL);
    runAction(seq);
}

