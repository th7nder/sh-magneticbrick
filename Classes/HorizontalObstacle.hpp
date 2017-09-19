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
CC_CONSTRUCTOR_ACCESS:

    
public:
    HorizontalObstacle();
    HorizontalState opened;
    
    static std::string leftTexture;
    static std::string centerTexture;
    static std::string rightTexture;
    
    virtual ~HorizontalObstacle();
    virtual void addSprite() override;
    virtual void setProperties(cocos2d::ValueMap& properties) override;
    
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override;
};
#endif /* HorizontalObstacle_hpp */
