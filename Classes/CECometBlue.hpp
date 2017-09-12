//
//  CECometBlue.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#ifndef CECometBlue_hpp
#define CECometBlue_hpp


#include "FlyingExtra.hpp"

class CECometBlue : public FlyingExtra
{
private:
    typedef CECometBlue self;
    typedef FlyingExtra super;
CC_CONSTRUCTOR_ACCESS:
    CECometBlue();
public:
    virtual ~CECometBlue();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};


#endif /* CECometBlue_hpp */
