//
//  GlidingRotatingExtra.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 11/07/2017.
//
//

#ifndef GlidingRotatingExtra_hpp
#define GlidingRotatingExtra_hpp

#include "SideExtra.hpp"

class GlidingRotatingExtra : public SideExtra
{
private:
    typedef GlidingRotatingExtra self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    GlidingRotatingExtra();
public:
    virtual ~GlidingRotatingExtra();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void launch() override;
    
};


#endif /* GlidingRotatingExtraExtra_hpp */
