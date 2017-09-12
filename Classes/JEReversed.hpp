//
//  JEReversed.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#ifndef JEReversed_hpp
#define JEReversed_hpp

#include "SideExtra.hpp"

class JEReversed : public SideExtra
{
private:
    typedef JEReversed self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    JEReversed();
public:
    virtual ~JEReversed();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};

#endif /* JEReversed_hpp */
