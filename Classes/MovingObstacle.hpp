//
//  MovingObstacle.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 15/03/2017.
//
//

#ifndef MovingObstacle_hpp
#define MovingObstacle_hpp

#include "HorizontalObstacle.hpp"
#include "DynamicLevelObject.hpp"

class MovingObstacle : public DynamicLevelObject
{
    typedef DynamicLevelObject super;
    typedef MovingObstacle self;
    float velocity;
    float stopX;
    
public:
    static std::string leftTexture;
    static std::string centerTexture;
    static std::string rightTexture;
    
    MovingObstacle();
    virtual ~MovingObstacle();
    virtual int getZ() const override;
    
    virtual void setProperties(cocos2d::ValueMap& props) override;
    virtual void addSprite() override;
    virtual void initPhysics(b2World* world) override;

    
    virtual void savePreviousStates() override;
    virtual void launch() override;
};

#endif /* MovingObstacle_hpp */
