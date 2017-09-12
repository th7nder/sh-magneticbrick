//
//  CSEBig.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 20/06/2017.
//
//

#ifndef CSEBig_hpp
#define CSEBig_hpp

#include "SideExtra.hpp"
class CSEBig : public SideExtra
{
private:
    typedef CSEBig self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    CSEBig();
public:
    virtual ~CSEBig();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};

#endif /* CSEBig_hpp */
