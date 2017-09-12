//
//  HETail.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#ifndef HETail_hpp
#define HETail_hpp

#include "SideExtra.hpp"

class HETail : public SideExtra
{
private:
    typedef HETail self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    HETail();
public:
    virtual ~HETail();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};

#endif /* HETail_hpp */
