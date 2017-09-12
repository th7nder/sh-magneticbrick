//
//  Parrot.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 11/07/2017.
//
//

#ifndef Parrot_hpp
#define Parrot_hpp

#include "GlidingRotatingExtra.hpp"

class Parrot : public GlidingRotatingExtra
{
private:
    typedef Parrot self;
    typedef GlidingRotatingExtra super;
CC_CONSTRUCTOR_ACCESS:
    Parrot();
public:
    virtual ~Parrot();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
};


#endif /* Parrot_hpp */
