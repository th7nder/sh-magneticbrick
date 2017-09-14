//
//  TH7Bridge.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 11/09/2017.
//
//

#include "TH7Bridge.hpp"
#include <platform/CCPlatformConfig.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include <platform/android/jni/JniHelper.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #include "Reachability.h"
#endif

bool TH7Bridge::isInternetAvailable()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    bool ret = false;
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "isConnectedToInternet", "()Z")) {
        jboolean result = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        if (result == JNI_TRUE) {
            ret = true;
            
        } else {
            ret = false;
        }
    }
    
    return ret;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Reachability *networkReachability = [Reachability reachabilityForInternetConnection];
    NetworkStatus networkStatus = [networkReachability currentReachabilityStatus];
    if (networkStatus == NotReachable)
    {
        return false;
    }
    else
    {
        return true;
    }
#else
    return false;
#endif
}

bool TH7Bridge::forceTouchAvailable()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    UIViewController* view = [UIApplication sharedApplication].keyWindow.rootViewController;
    if ([view respondsToSelector:@selector(traitCollection)] &&
        [view.traitCollection respondsToSelector:@selector(forceTouchCapability)] &&
        view.traitCollection.forceTouchCapability == UIForceTouchCapabilityAvailable) {
        return true;
    }

    return false;
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return false;
#endif
}
