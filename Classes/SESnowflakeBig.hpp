//
//  SESnowflakeBig.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#ifndef SESnowflakeBig_hpp
#define SESnowflakeBig_hpp

#include "FlyingRotatingExtra.hpp"

class SESnowflakeBig : public FlyingRotatingExtra
{
private:
    typedef SESnowflakeBig self;
    typedef FlyingRotatingExtra super;
CC_CONSTRUCTOR_ACCESS:
    SESnowflakeBig();
public:
    virtual ~SESnowflakeBig();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};

#endif /* SESnowflakeBig_hpp */
