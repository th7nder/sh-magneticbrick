#LOCAL_PATH
LOCAL_PATH := /Users/konrad/dev/src/skyhorn/MagneticBrick/proj.android-studio/app/jni
include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)
$(call import-add-path,$(LOCAL_PATH))

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
$(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
$(LOCAL_PATH)/../../../Classes/B2DebugDrawLayer.cpp \
$(LOCAL_PATH)/../../../Classes/FinishLine.cpp \
$(LOCAL_PATH)/../../../Classes/GB2ShapeCacheX.cpp \
$(LOCAL_PATH)/../../../Classes/GLESRender.cpp \
$(LOCAL_PATH)/../../../Classes/GameHandler.cpp \
$(LOCAL_PATH)/../../../Classes/GameScene.cpp \
$(LOCAL_PATH)/../../../Classes/Globals.cpp \
$(LOCAL_PATH)/../../../Classes/HorizontalObstacle.cpp \
$(LOCAL_PATH)/../../../Classes/Laser.cpp \
$(LOCAL_PATH)/../../../Classes/Level.cpp \
$(LOCAL_PATH)/../../../Classes/LevelObject.cpp \
$(LOCAL_PATH)/../../../Classes/LoadingScene.cpp \
$(LOCAL_PATH)/../../../Classes/WaitLayout.cpp \
$(LOCAL_PATH)/../../../Classes/MovingObstacle.cpp \
$(LOCAL_PATH)/../../../Classes/Player.cpp \
$(LOCAL_PATH)/../../../Classes/SHButton.cpp \
$(LOCAL_PATH)/../../../Classes/SHLevel.cpp \
$(LOCAL_PATH)/../../../Classes/SHSlider.cpp \
$(LOCAL_PATH)/../../../Classes/SHSliderBox.cpp \
$(LOCAL_PATH)/../../../Classes/SHSwitch.cpp \
$(LOCAL_PATH)/../../../Classes/SHSwitchBox.cpp \
$(LOCAL_PATH)/../../../Classes/SelectLayout.cpp \
$(LOCAL_PATH)/../../../Classes/SettingsLayout.cpp \
$(LOCAL_PATH)/../../../Classes/Star.cpp \
$(LOCAL_PATH)/../../../Classes/Switch.cpp \
$(LOCAL_PATH)/../../../Classes/TeleportIn.cpp \
$(LOCAL_PATH)/../../../Classes/TeleportOut.cpp \
$(LOCAL_PATH)/../../../Classes/Walls.cpp \
$(LOCAL_PATH)/../../../Classes/MeltingObstacle.cpp \
$(LOCAL_PATH)/../../../Classes/Theme.cpp \
$(LOCAL_PATH)/../../../Classes/ThemeManager.cpp \
$(LOCAL_PATH)/../../../Classes/TitleLayout.cpp \
$(LOCAL_PATH)/../../../Classes/Touchable.cpp \
$(LOCAL_PATH)/../../../Classes/VerticalObstacle.cpp \
$(LOCAL_PATH)/../../../Classes/VisibleRect.cpp \
$(LOCAL_PATH)/../../../Classes/WinLoseLayout.cpp \
$(LOCAL_PATH)/../../../Classes/PostEffectNode.cpp \
$(LOCAL_PATH)/../../../Classes/Bullet.cpp \
$(LOCAL_PATH)/../../../Classes/BulletTimeStart.cpp \
$(LOCAL_PATH)/../../../Classes/BulletTimeEnd.cpp \
$(LOCAL_PATH)/../../../Classes/BlackoutStart.cpp \
$(LOCAL_PATH)/../../../Classes/BlackoutStop.cpp \
$(LOCAL_PATH)/../../../Classes/Gravity.cpp \
$(LOCAL_PATH)/../../../Classes/TriggerMelting.cpp \
$(LOCAL_PATH)/../../../Classes/Skin.cpp \
$(LOCAL_PATH)/../../../Classes/SkinManager.cpp \
$(LOCAL_PATH)/../../../Classes/ShopLayout.cpp \
$(LOCAL_PATH)/../../../Classes/RewardLayout.cpp \
$(LOCAL_PATH)/../../../Classes/PopupLayout.cpp \
$(LOCAL_PATH)/../../../Classes/TutorialLayout.cpp \
$(LOCAL_PATH)/../../../Classes/KielniaLayout.cpp \
$(LOCAL_PATH)/../../../Classes/BlurFromTo.cpp \
$(LOCAL_PATH)/../../../Classes/SHShopItem.cpp \
$(LOCAL_PATH)/../../../Classes/SHShopBonusItem.cpp \
$(LOCAL_PATH)/../../../Classes/BacteriaBlue.cpp \
$(LOCAL_PATH)/../../../Classes/BacteriaPink.cpp \
$(LOCAL_PATH)/../../../Classes/BacteriaGreen.cpp \
$(LOCAL_PATH)/../../../Classes/InfectionStart.cpp \
$(LOCAL_PATH)/../../../Classes/InfectionStop.cpp \
$(LOCAL_PATH)/../../../Classes/SideExtra.cpp \
$(LOCAL_PATH)/../../../Classes/CSESmall.cpp \
$(LOCAL_PATH)/../../../Classes/CSEMedium.cpp \
$(LOCAL_PATH)/../../../Classes/CSEBig.cpp \
$(LOCAL_PATH)/../../../Classes/CSEBarrier.cpp \
$(LOCAL_PATH)/../../../Classes/CSEBall.cpp \
$(LOCAL_PATH)/../../../Classes/JEDouble.cpp \
$(LOCAL_PATH)/../../../Classes/JETriple.cpp \
$(LOCAL_PATH)/../../../Classes/JEReversed.cpp \
$(LOCAL_PATH)/../../../Classes/DESkull.cpp \
$(LOCAL_PATH)/../../../Classes/DECactus.cpp \
$(LOCAL_PATH)/../../../Classes/CECometBlue.cpp \
$(LOCAL_PATH)/../../../Classes/CECometRed.cpp \
$(LOCAL_PATH)/../../../Classes/CEAlienRed.cpp \
$(LOCAL_PATH)/../../../Classes/CEAlienBlue.cpp \
$(LOCAL_PATH)/../../../Classes/CEAlienGreen.cpp \
$(LOCAL_PATH)/../../../Classes/WEBoot.cpp \
$(LOCAL_PATH)/../../../Classes/WEHat.cpp \
$(LOCAL_PATH)/../../../Classes/WEPistol.cpp \
$(LOCAL_PATH)/../../../Classes/SESnowflakeBig.cpp \
$(LOCAL_PATH)/../../../Classes/SESnowflakeSmall.cpp \
$(LOCAL_PATH)/../../../Classes/HETrident.cpp \
$(LOCAL_PATH)/../../../Classes/HETail.cpp \
$(LOCAL_PATH)/../../../Classes/HESkull.cpp \
$(LOCAL_PATH)/../../../Classes/UEFishOrange.cpp \
$(LOCAL_PATH)/../../../Classes/UEFishGreen.cpp \
$(LOCAL_PATH)/../../../Classes/UEFishRed.cpp \
$(LOCAL_PATH)/../../../Classes/UETentacle.cpp \
$(LOCAL_PATH)/../../../Classes/FlyingExtra.cpp \
$(LOCAL_PATH)/../../../Classes/FlyingRotatingExtra.cpp \
$(LOCAL_PATH)/../../../Classes/GlidingExtra.cpp \
$(LOCAL_PATH)/../../../Classes/LevelFollower.cpp \
$(LOCAL_PATH)/../../../Classes/GlidingRotatingExtra.cpp \
$(LOCAL_PATH)/../../../Classes/Parrot.cpp \
$(LOCAL_PATH)/../../../Classes/constants.cpp

LOCAL_CPPFLAGS := -DSDKBOX_ENABLED
LOCAL_LDLIBS := -landroid \
-llog
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes
LOCAL_SHARED_LIBRARIES := libadcolonyso \
libjsso \
libadcolonyso \
libjsso
LOCAL_WHOLE_STATIC_LIBRARIES := PluginAdMob \
sdkbox \
PluginAdColony \
PluginIAP \
android_native_app_glue \
PluginChartboost \
PluginUnityAds

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module, ./sdkbox)
$(call import-module, ./pluginadmob)
$(call import-module, ./pluginadcolony)
$(call import-module, ./pluginiap)
$(call import-module, ./pluginchartboost)
$(call import-module, ./pluginunityads)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
