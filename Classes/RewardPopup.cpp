//
//  RewardPopup.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/10/2017.
//

#include "RewardPopup.hpp"

RewardPopup* RewardPopup::create(GameHandler *gameHandler, const std::string &icon, int lowValue, int highValue)
{
    RewardPopup * ret = new (std::nothrow) RewardPopup();
    if (ret && ret->init(gameHandler, icon, lowValue, highValue))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}


bool RewardPopup::init(GameHandler *gameHandler, const std::string &icon, int lowValue, int highValue)
{
    if(!super::init()) return false;

    return true;
}


