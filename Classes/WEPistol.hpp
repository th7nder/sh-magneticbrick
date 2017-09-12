//
//  WEPistol.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#ifndef WEPistol_hpp
#define WEPistol_hpp

#include "SideExtra.hpp"

class WEPistol : public SideExtra
{
private:
    typedef WEPistol self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    WEPistol();
public:
    virtual ~WEPistol();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};

#endif /* WEPistol_hpp */
