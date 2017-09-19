//
//  Bullet.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 01/06/2017.
//
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "DynamicLevelObject.hpp"
#include "Globals.hpp"

class Bullet : public DynamicLevelObject
{
private:
    typedef Bullet self;
    typedef DynamicLevelObject super;
    
    b2Vec2 velocity;
    float angle;
CC_CONSTRUCTOR_ACCESS:
    Bullet();
public:
    virtual ~Bullet();
    virtual void setProperties(cocos2d::ValueMap& props) override;
    virtual void addSprite() override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* otherBody) override {return true;};
    
    virtual void initPhysics(b2World* world) override;
    virtual void launch() override;
    
};


#endif /* Bullet_hpp */
