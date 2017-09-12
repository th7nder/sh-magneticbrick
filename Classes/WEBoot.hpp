//
//  WEBoot.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#ifndef WEBoot_hpp
#define WEBoot_hpp

#include "FlyingRotatingExtra.hpp"

class WEBoot : public FlyingRotatingExtra
{
private:
    typedef WEBoot self;
    typedef FlyingRotatingExtra super;
CC_CONSTRUCTOR_ACCESS:
    WEBoot();
public:
    virtual ~WEBoot();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};

#endif /* WEBoot_hpp */
