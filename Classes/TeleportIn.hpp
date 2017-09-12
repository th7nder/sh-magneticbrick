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
#include "GameHandler.hpp"
#include "LevelObject.hpp"

class TeleportIn : public LevelObject
{
    typedef LevelObject super;
    typedef TeleportIn self;
    
    int textureSize;
    float velocity;

CC_CONSTRUCTOR_ACCESS:
    TeleportIn();
public:
    virtual std::string getDescription() const override
    {
        return "TeleportIn";
    }
    
    float getVelocity() const
    {
        return velocity;
    }
    virtual ~TeleportIn();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    virtual void addSprite() override;
    
    virtual void setProperties(ValueMap &properties) override;
    
    virtual void initPhysics(b2World* world) override;
    std::string target;
};

#endif /* TeleportIn_hpp */
