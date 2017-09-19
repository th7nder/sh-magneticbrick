//
//  TeleportOut.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/03/2017.
//
//

#ifndef TeleportOut_hpp
#define TeleportOut_hpp

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "LevelObject.hpp"
#include "Globals.hpp"

class TeleportOut : public LevelObject
{
    typedef LevelObject super;
    typedef TeleportOut self;
    
    int textureSize;
public:
    TeleportOut();
    virtual std::string getDescription() const override
    {
        return "TeleportOut";
    }
    
    virtual ~TeleportOut();
    virtual void setProperties(cocos2d::ValueMap &properties) override;
    virtual void addSprite() override;
    virtual void initPhysics(b2World* world) override;
};

#endif /* TeleportOut_hpp */
