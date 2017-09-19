//
//  Gravity.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 13/06/2017.
//
//

#ifndef Gravity_hpp
#define Gravity_hpp

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Globals.hpp"
#include "LevelObject.hpp"
#include "SimpleAudioEngine.h"

class Level;
class Gravity : public LevelObject
{
private:
    typedef LevelObject super;
    typedef Gravity self;
    
CC_CONSTRUCTOR_ACCESS:
    Gravity();
    virtual ~Gravity();
public:
    virtual void addSprite() override;
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override;
    virtual bool OnContactEnd(LevelObject* other) override;
    
};


#endif /* Gravity_hpp */
