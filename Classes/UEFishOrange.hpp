//
//  UEFishOrange.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#ifndef UEFishOrange_hpp
#define UEFishOrange_hpp

#include "GlidingExtra.hpp"

class UEFishOrange : public GlidingExtra
{
private:
    typedef UEFishOrange self;
    typedef GlidingExtra super;
CC_CONSTRUCTOR_ACCESS:
    UEFishOrange();
public:
    virtual ~UEFishOrange();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
};


#endif /* UEFishOrange_hpp */
