//
//  CEAlienRed.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#ifndef CEAlienRed_hpp
#define CEAlienRed_hpp

#include "SideExtra.hpp"

class CEAlienRed : public SideExtra
{
private:
    typedef CEAlienRed self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    CEAlienRed();
public:
    virtual ~CEAlienRed();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};



#endif /* CEAlienRed_hpp */
