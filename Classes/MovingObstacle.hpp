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

class MovingObstacle : public HorizontalObstacle
{
    typedef MovingObstacle self;
    typedef HorizontalObstacle super;
    float velocity;
    float stopX;
    
CC_CONSTRUCTOR_ACCESS:
    MovingObstacle();
public:
    virtual int getZ() const override
    {
        return 4;
    }
    virtual ~MovingObstacle();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    virtual void initPhysics(b2World* world) override;
    virtual void setProperties(ValueMap& props) override;
    
    virtual void interpolate(float alpha) override;
    virtual void savePreviousStates() override;
    virtual void launch() override;
};

#endif /* MovingObstacle_hpp */
