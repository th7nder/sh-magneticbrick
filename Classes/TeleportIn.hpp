//
//  TeleportIn.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/03/2017.
//
//

#ifndef TeleportIn_hpp
#define TeleportIn_hpp

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "LevelObject.hpp"
#include "Globals.hpp"

class TeleportIn : public LevelObject
{
    typedef LevelObject super;
    typedef TeleportIn self;
    
    int textureSize;
    float velocity;

    
public:
    TeleportIn();
    virtual std::string getDescription() const override
    {
        return "TeleportIn";
    }
    
    float getVelocity() const
    {
        return velocity;
    }
    virtual ~TeleportIn();
    
    virtual void setProperties(cocos2d::ValueMap &properties) override;
    virtual void addSprite() override;
    virtual void initPhysics(b2World* world) override;
    
    std::string target;
};

#endif /* TeleportIn_hpp */
