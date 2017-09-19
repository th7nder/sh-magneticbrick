//
//  LevelObject.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 30/01/2017.
//
//



#include "LevelObject.hpp"
USING_NS_CC;

LevelObject::LevelObject() :
body(nullptr),
sprite(nullptr),
remove(false)
{
    
}

LevelObject::~LevelObject()
{
    if(body)
    {
        body->GetWorld()->DestroyBody(body);
    }

}


std::string LevelObject::getDescription() const
{
    return "LevelObject";
}

int LevelObject::getZ() const 
{
    return 1;
}

bool LevelObject::isDynamic() const
{
    return false;
}

Sprite* LevelObject::getSprite()
{
    return sprite;
}

b2Body* LevelObject::getBody()
{
    return body;
}



void LevelObject::setProperties(ValueMap &properties)
{
    CCASSERT(!properties["width"].isNull(), "LevelObject -> width isNull");
    CCASSERT(!properties["height"].isNull(), "LevelObject -> height isNull");
    
    auto scale =_director->getContentScaleFactor();
    
    float width = (properties["width"].asFloat() / 1080.0) * 640 * scale;
    float height = (properties["height"].asFloat() / 1920.0) * 1136 * scale;
    
    float x = properties["x"].asFloat() / 1080.0 * 640 * scale;
    x += width / 2;
    float y = properties["y"].asFloat() / 1920.0 * 1136 * scale;
    y += height / 2;
    
    
    setAnchorPoint(Vec2(0.5, 0.5));
    setPosition(Vec2(x, y));
    setContentSize(Size(width, height));
}

void LevelObject::initPhysics(b2World* world)
{
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPositionX(), getPositionY()));
    body->CreateFixture(createFixture(createRectangularShape(size.width, size.height)));
}


bool LevelObject::OnContactBegin(LevelObject *other, b2Body *body)
{
    return false;
}

bool LevelObject::OnContactEnd(LevelObject *other)
{
    return false;
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

