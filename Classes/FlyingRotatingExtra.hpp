//
//  FlyingRotatingExtra.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#ifndef FlyingRotatingExtra_hpp
#define FlyingRotatingExtra_hpp

#include "SideExtra.hpp"

class FlyingRotatingExtra : public SideExtra
{
private:
    typedef FlyingRotatingExtra self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    FlyingRotatingExtra();
public:
    virtual ~FlyingRotatingExtra();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void launch() override;
    
};


#endif /* FlyingRotatingExtra_hpp */
