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
#include "GameHandler.hpp"
#include "LevelObject.hpp"

class TeleportOut : public LevelObject
{
    typedef LevelObject super;
    typedef TeleportOut self;
    
    int textureSize;
CC_CONSTRUCTOR_ACCESS:
    TeleportOut();
public:
    virtual std::string getDescription() const override
    {
        return "TeleportOut";
    }
    
    virtual ~TeleportOut();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    virtual void addSprite() override;
    
    virtual void setProperties(ValueMap &properties) override;
    
    virtual void initPhysics(b2World* world) override;
};

#endif /* TeleportOut_hpp */
