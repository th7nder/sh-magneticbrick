//
//  LevelFollower.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 28/06/2017.
//
//

#ifndef LevelFollower_hpp
#define LevelFollower_hpp

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "LevelObject.hpp"
#include "GameHandler.hpp"

class LevelFollower : public LevelObject
{
private:
    typedef LevelObject super;
    typedef LevelFollower self;
CC_CONSTRUCTOR_ACCESS:
    LevelFollower();
    b2Body* rightBody;
    float speed;
    
public:
    virtual ~LevelFollower();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    virtual void setProperties(ValueMap& props) override;
    virtual void initPhysics(b2World* world) override;
    b2Body* createDestroyer(b2World* world, float x, float y);
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override {return true;}
    
    virtual void interpolate(float alpha) override;
    virtual void savePreviousStates() override;
    
};
#endif /* LevelFollower_hpp */
