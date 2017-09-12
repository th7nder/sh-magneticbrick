//
//  JETriple.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#ifndef JETriple_hpp
#define JETriple_hpp

#include "SideExtra.hpp"

class JETriple : public SideExtra
{
private:
    typedef JETriple self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    JETriple();
public:
    virtual ~JETriple();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};


#endif /* JETriple_hpp */
