//
//  UEFishGreen.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#ifndef UEFishGreen_hpp
#define UEFishGreen_hpp

#include "GlidingExtra.hpp"

class UEFishGreen : public GlidingExtra
{
private:
    typedef UEFishGreen self;
    typedef GlidingExtra super;
CC_CONSTRUCTOR_ACCESS:
    UEFishGreen();
public:
    virtual ~UEFishGreen();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
};


#endif /* UEFishGreen_hpp */
