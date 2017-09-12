//
//  UEFishRed.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#ifndef UEFishRed_hpp
#define UEFishRed_hpp

#include "GlidingExtra.hpp"

class UEFishRed : public GlidingExtra
{
private:
    typedef UEFishRed self;
    typedef GlidingExtra super;
CC_CONSTRUCTOR_ACCESS:
    UEFishRed();
public:
    virtual ~UEFishRed();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
};

#endif /* UEFishRed_hpp */
