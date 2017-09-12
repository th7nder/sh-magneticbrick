//
//  VerticalObstacle.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 18/03/2017.
//
//

#ifndef VerticalObstacle_hpp
#define VerticalObstacle_hpp

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "GameHandler.hpp"
#include "LevelObject.hpp"

class VerticalObstacle : public LevelObject
{
    typedef LevelObject super;
    typedef VerticalObstacle self;
    float angle;
CC_CONSTRUCTOR_ACCESS:
    VerticalObstacle();
    std::string downTexture;
    std::string centerTexture;
    std::string upTexture;
public:
    virtual int getZ() const override
    {
        return 10;
    }
    virtual ~VerticalObstacle();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    virtual void addSprite() override;
    
    virtual bool OnContactBegin(LevelObject* other, b2Body* otherBody) override {return true;};
    virtual void setProperties(ValueMap& props) override;
    virtual void initPhysics(b2World* world) override;
};

#endif /* VerticalObstacle_hpp */
