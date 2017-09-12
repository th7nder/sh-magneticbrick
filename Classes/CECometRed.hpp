//
//  CECometRed.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#ifndef CECometRed_hpp
#define CECometRed_hpp


#include "FlyingExtra.hpp"

class CECometRed : public FlyingExtra
{
private:
    typedef CECometRed self;
    typedef FlyingExtra super;
CC_CONSTRUCTOR_ACCESS:
    CECometRed();
public:
    virtual ~CECometRed();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};

#endif /* CECometRed_hpp */
