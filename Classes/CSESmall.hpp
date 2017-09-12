//
//  CSESmall.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 20/06/2017.
//
//

#ifndef CSESmall_hpp
#define CSESmall_hpp

#include "LevelObject.hpp"
#include "SideExtra.hpp"

class CSESmall : public SideExtra
{
private:
    typedef CSESmall self;
    typedef SideExtra super;
CC_CONSTRUCTOR_ACCESS:
    CSESmall();
public:
    virtual ~CSESmall();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    
};

#endif /* CSESmall_hpp */
