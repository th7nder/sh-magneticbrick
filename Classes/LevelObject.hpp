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
#include "GameHandler.hpp"

using namespace cocos2d;
class GameNode;

class LevelObject : public Node
{
private:
    typedef LevelObject self;
    typedef Node super;
CC_CONSTRUCTOR_ACCESS:
    LevelObject();
    GameHandler* gameHandler;
    Sprite* sprite;
    b2Body* body;
    float startX;
    float startY;
    float width;
    float height;
    bool remove;
    
    cocos2d::Vec2 previousPosition;
    
public:
    virtual std::string getDescription() const override
    {
        return "LevelObject";
    }
    virtual int getZ() const
    {
        return 1;
    }
    
    Sprite* getSprite()
    {
        return sprite;
    }
    
    static cocos2d::Size ownVisibleSize;
    virtual ~LevelObject();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler);
    
    virtual void interpolate(float alpha) {};
    virtual void update(float dt) {};
    virtual void setProperties(ValueMap& props);
    virtual void addSprite() {};
    virtual void initPhysics(b2World* world);
    virtual b2BodyDef* createBody(float x, float y);
    virtual b2PolygonShape* createRectangularShape(float width, float height);
    virtual b2CircleShape* createCircleShape(float radius);
    virtual b2FixtureDef* createFixture(b2Shape* shape);
    
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) {return false;};
    virtual bool OnContactEnd(LevelObject* other) {return false;};
    virtual void savePreviousStates() {}
    virtual void scheduleRemove(float time);
    virtual void launch() {};
    
    virtual b2Body* getBody() {return body;}
    
    

};


#endif /* LevelObject_hpp */
