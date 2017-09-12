//
//  CSEMedium.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 20/06/2017.
//
//

#ifndef CSEMedium_hpp
#define CSEMedium_hpp

#include "SideExtra.hpp"
class CSEMedium : public SideExtra
{
private:
    typedef CSEMedium self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    CSEMedium();
public:
    virtual ~CSEMedium();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};

#endif /* CSEMedium_hpp */
