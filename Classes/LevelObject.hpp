//
//  LevelObject.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 30/01/2017.
//
//

#ifndef LevelObject_hpp
#define LevelObject_hpp

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "constants.cpp"

class LevelObject : public cocos2d::Node
{
private:
    typedef LevelObject self;
    typedef Node super;
protected:
    cocos2d::Sprite* sprite;
    b2Body* body;
    bool remove;
    
public:
    LevelObject();
    virtual ~LevelObject();
    virtual std::string getDescription() const override;
    virtual int getZ() const;
    virtual bool isDynamic() const;
    cocos2d::Sprite* getSprite();
    b2Body* getBody();
    

    virtual void setProperties(cocos2d::ValueMap& props);
    virtual void addSprite() {};
    virtual void initPhysics(b2World* world);
    virtual b2BodyDef* createBody(const cocos2d::Vec2& pos);
    virtual b2PolygonShape* createRectangularShape(const cocos2d::Size& size);
    virtual b2CircleShape* createCircleShape(float radius);
    virtual b2FixtureDef* createFixture(b2Shape* shape);
    
    virtual bool OnContactBegin(LevelObject* other, b2Body* body);
    virtual bool OnContactEnd(LevelObject* other);
    
    virtual void queueToRemove();
    

};


#endif /* LevelObject_hpp */
