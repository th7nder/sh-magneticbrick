//
//  HESkull.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#ifndef HESkull_hpp
#define HESkull_hpp

#include "FlyingRotatingExtra.hpp"

class HESkull : public FlyingRotatingExtra
{
private:
    typedef HESkull self;
    typedef FlyingRotatingExtra super;
CC_CONSTRUCTOR_ACCESS:
    HESkull();
public:
    virtual ~HESkull();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
};


#endif /* HESkull_hpp */
