//
//  CSEBall.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 20/06/2017.
//
//

#ifndef CSEBall_hpp
#define CSEBall_hpp

#include "SideExtra.hpp"
class CSEBall : public SideExtra
{
private:
    typedef CSEBall self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    CSEBall();
public:
    virtual ~CSEBall();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};

#endif /* CSEBall_hpp */
