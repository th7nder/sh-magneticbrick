//
//  CEAlienGreen.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#ifndef CEAlienGreen_hpp
#define CEAlienGreen_hpp

#include "SideExtra.hpp"

class CEAlienGreen : public SideExtra
{
private:
    typedef CEAlienGreen self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    CEAlienGreen();
public:
    virtual ~CEAlienGreen();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};



#endif /* CEAlienGreen_hpp */
