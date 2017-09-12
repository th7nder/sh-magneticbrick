//
//  CSEBarrier.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 20/06/2017.
//
//

#ifndef CSEBarrier_hpp
#define CSEBarrier_hpp

#include "SideExtra.hpp"
class CSEBarrier : public SideExtra
{
private:
    typedef CSEBarrier self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    CSEBarrier();
public:
    virtual ~CSEBarrier();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};

#endif /* CSEBarrier_hpp */
