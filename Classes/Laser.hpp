//
//  Laser.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 02/02/2017.
//
//

#ifndef Laser_hpp
#define Laser_hpp

#include "cocos2d.h"
#include "HorizontalObstacle.hpp"

class Laser : public HorizontalObstacle
{
    typedef Laser self;
    typedef HorizontalObstacle super;
protected:
    Laser();
public:
    virtual ~Laser();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    virtual void setProperties(ValueMap& properties) override;
};

#endif /* Laser_hpp */
