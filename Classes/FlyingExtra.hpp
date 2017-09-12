//
//  FlyingExtra.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#ifndef FlyingExtra_hpp
#define FlyingExtra_hpp

#include "SideExtra.hpp"

class FlyingExtra : public SideExtra
{
private:
    typedef FlyingExtra self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    FlyingExtra();
public:
    virtual ~FlyingExtra();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void launch() override;
    
};


#endif /* FlyingExtra_hpp */
