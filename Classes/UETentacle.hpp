//
//  UETentacle.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#ifndef UETentacle_hpp
#define UETentacle_hpp

#include "SideExtra.hpp"

class UETentacle : public SideExtra
{
private:
    typedef UETentacle self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    UETentacle();
public:
    virtual ~UETentacle();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};

#endif /* UETentacle_hpp */
