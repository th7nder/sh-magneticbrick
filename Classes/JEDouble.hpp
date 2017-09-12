//
//  JEDouble.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#ifndef JEDouble_hpp
#define JEDouble_hpp

#include "SideExtra.hpp"

class JEDouble : public SideExtra
{
private:
    typedef JEDouble self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    JEDouble();
public:
    virtual ~JEDouble();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};


#endif /* JEDouble_hpp */
