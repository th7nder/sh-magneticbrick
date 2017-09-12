//
//  SESnowflakeSmall.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#ifndef SESnowflakeSmall_hpp
#define SESnowflakeSmall_hpp

#include "FlyingRotatingExtra.hpp"

class SESnowflakeSmall : public FlyingRotatingExtra
{
private:
    typedef SESnowflakeSmall self;
    typedef FlyingRotatingExtra super;
CC_CONSTRUCTOR_ACCESS:
    SESnowflakeSmall();
public:
    virtual ~SESnowflakeSmall();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
};


#endif /* SESnowflakeSmall_hpp */
