//
//  HorizontalObstacle.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 30/01/2017.
//
//

#ifndef HorizontalObstacle_hpp
#define HorizontalObstacle_hpp

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "GameHandler.hpp"
#include "LevelObject.hpp"

class HorizontalObstacle : public LevelObject
{
    enum HorizontalState
    {
        Closed = 0,
        LeftOpened = 1,
        RightOpened = 2,
        BothOpened = 3
    };
    typedef LevelObject super;
    typedef HorizontalObstacle self;
    bool physics;
CC_CONSTRUCTOR_ACCESS:
    HorizontalObstacle();
    std::string leftTexture;
    std::string centerTexture;
    std::string rightTexture;
public:
    HorizontalState opened;
    virtual ~HorizontalObstacle();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    virtual void addSprite() override;
    virtual void setProperties(ValueMap& properties) override;
    
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override
    {
        return true;
    };
};
#endif /* HorizontalObstacle_hpp */
