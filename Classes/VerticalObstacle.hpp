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
public:
    VerticalObstacle();
    static std::string downTexture;
    static std::string centerTexture;
    static std::string upTexture;
    
    virtual int getZ() const override
    {
        return 10;
    }
    virtual ~VerticalObstacle();
    virtual void addSprite() override;
    virtual void setProperties(cocos2d::ValueMap& props) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* otherBody) override {return true;};

};

#endif /* VerticalObstacle_hpp */
