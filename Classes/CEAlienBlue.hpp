//
//  CEAlienBlue.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#ifndef CEAlienBlue_hpp
#define CEAlienBlue_hpp

#include "SideExtra.hpp"

class CEAlienBlue : public SideExtra
{
private:
    typedef CEAlienBlue self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    CEAlienBlue();
public:
    virtual ~CEAlienBlue();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};



#endif /* CEAlienBlue_hpp */
