//
//  WEHat.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#ifndef WEHat_hpp
#define WEHat_hpp

#include "FlyingRotatingExtra.hpp"

class WEHat : public FlyingRotatingExtra
{
private:
    typedef WEHat self;
    typedef FlyingRotatingExtra super;
CC_CONSTRUCTOR_ACCESS:
    WEHat();
public:
    virtual ~WEHat();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};

#endif /* WEHat_hpp */
