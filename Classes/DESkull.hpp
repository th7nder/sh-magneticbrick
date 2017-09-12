//
//  DESkull.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#ifndef DESkull_hpp
#define DESkull_hpp


#include "FlyingRotatingExtra.hpp"

class DESkull : public FlyingRotatingExtra
{
private:
    typedef DESkull self;
    typedef FlyingRotatingExtra super;
CC_CONSTRUCTOR_ACCESS:
    DESkull();
public:
    virtual ~DESkull();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};



#endif /* DESkull_hpp */
