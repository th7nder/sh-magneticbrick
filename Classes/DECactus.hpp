//
//  DECactus.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#ifndef DECactus_hpp
#define DECactus_hpp


#include "SideExtra.hpp"

class DECactus : public SideExtra
{
private:
    typedef DECactus self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    DECactus();
public:
    virtual ~DECactus();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};


#endif /* DECactus_hpp */
