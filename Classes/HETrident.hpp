//
//  HETrident.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#ifndef HETrident_hpp
#define HETrident_hpp

#include "SideExtra.hpp"

class HETrident : public SideExtra
{
private:
    typedef HETrident self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    HETrident();
public:
    virtual ~HETrident();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};


#endif /* HETrident_hpp */
