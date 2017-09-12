//
//  GlidingExtra.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#ifndef GlidingExtra_hpp
#define GlidingExtra_hpp


#include "SideExtra.hpp"

class GlidingExtra : public SideExtra
{
private:
    typedef GlidingExtra self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    GlidingExtra();
public:
    virtual ~GlidingExtra();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void launch() override;
    
};

#endif /* GlidingExtra_hpp */
