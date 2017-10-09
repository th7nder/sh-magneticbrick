//
//  Globals.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 11/03/2017.



#include "Globals.hpp"



std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);
    
    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }
    
    return result;
}

void playClickSound()
{
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->playEffect(Globals::resources["effect_click"].c_str());
}

const std::string Globals::gameFont = "fonts/Montserrat-Regular.ttf";
const std::string Globals::gameFontBold = "fonts/Montserrat-Bold.ttf";
const int Globals::startingBricks = 20;
const int Globals::startingThemeId = 0;
const int Globals::startingKielnias = 10;
const int Globals::startingMusicVolume = 40;
const int Globals::startingSfxVolume = 30;

const int Globals::chaptersSteps[] = {0, 9,18,30,40,58,78,100,125,150};
const int Globals::bricksSteps[] = {0, 9,18,27,36,54, 63, 72, 81, 90, 99, 108, 117, 126, 135, 144};

const int Globals::bricksAfterWaiting = 20;
const int Globals::timeToWait = 90;
const float Globals::blurRadius = 2.6f;//  2.6
const float Globals::backgroundSpeed = 450.0f;
bool Globals::iapLoaded = false;
bool Globals::smallPhone = false;

std::unordered_map<std::string, std::string> Globals::resources = Globals::initializeResources();

std::unordered_map<std::string, std::string> Globals::initializeResources()
{
    std::unordered_map<std::string, std::string> resources;
    
    
    resources["barstar_empty"] = "ui/level/barstar_empty.png";
    resources["barstar_full"] = "ui/level/barstar_full.png";
    
    resources["splashscreen"] = "splash.png";
    resources["icon_loadingbar"] = "buttons/loadingbar.png";
    resources["logo_mb"] = "mb-logo.png";
    
    resources["icon_back_left_black"] = "buttons/back_black.png";
    resources["icon_back_left_white"] = "buttons/back_white.png";
    resources["icon_back_right_black"] = "buttons/back_right_black.png";
    resources["icon_back_right_white"] = "buttons/back_right_white.png";

    resources["icon_cart_black"] = "buttons/cart_black.png";
    resources["icon_cart_white"] = "buttons/cart_white.png";
    resources["icon_settings_black"] = "buttons/settings_black.png";
    resources["icon_settings_white"] = "buttons/settings_white.png";
    resources["icon_home_black"] = "buttons/home_black.png";
    resources["icon_home_white"] = "buttons/home_white.png";
    
    resources["icon_minus_black"] = "buttons/minus_black.png";
    resources["icon_minus_white"] = "buttons/minus_white.png";
    
    resources["icon_plus_black"] = "buttons/plus_black.png";
    resources["icon_plus_white"] = "buttons/plus_white.png";
    
    resources["icon_line_black"] = "buttons/slider_black.png";
    resources["icon_line_white"] = "buttons/slider_white.png";
    resources["icon_dot_black"] = "buttons/dot_black.png";
    resources["icon_dot_white"] = "buttons/dot_white.png";
    
    resources["icon_forcetouch_black"] = "buttons/forcetouch_black.png";
    resources["icon_forcetouch_white"] = "buttons/forcetouch_white.png";
    resources["icon_sfx_black"] = "buttons/sfx_black.png";
    resources["icon_sfx_white"] = "buttons/sfx_white.png";
    resources["icon_music_black"] = "buttons/music_black.png";
    resources["icon_music_white"] = "buttons/music_white.png";
    
    resources["icon_star_empty_black"] = "buttons/icon_star_empty_black.png";
    resources["icon_star_empty_white"] = "buttons/icon_star_empty_white.png";
    resources["icon_star_full_black"] = "buttons/icon_star_full_black.png";
    resources["icon_star_full_white"] = "buttons/icon_star_full_white.png";
    
    resources["icon_kielnia_black"] = "buttons/icon_kielnia_black.png";
    resources["icon_kielnia_white"] = "buttons/icon_kielnia_white.png";
    

    resources["icon_off_black"] = "buttons/off_black.png";
    resources["icon_on_black"] = "buttons/on_black.png";
    resources["icon_off_white"] = "buttons/off_white.png";
    resources["icon_on_white"] = "buttons/on_white.png";
    

    resources["icon_kielnia_add"] = "buttons/icon_kielnia_add.png";

    resources["shop_tab_bricks_white"] = "buttons/shop_tab_bricks_white.png";
    resources["shop_tab_bonus_white"] = "buttons/shop_tab_bonus_white.png";
    resources["shop_tab_bricks_black"] = "buttons/shop_tab_bricks_black.png";
    resources["shop_tab_bonus_black"] = "buttons/shop_tab_bonus_black.png";
    
    resources["shop_star_indicator_white"] = "buttons/shop_star_indicator_white.png";
    resources["shop_star_indicator_black"] = "buttons/shop_star_indicator_black.png";
    
    resources["shop_bigstar_indicator_white"] = "buttons/shop_bigstar_indicator_white.png";
    resources["shop_bigstar_indicator_black"] = "buttons/shop_bigstar_indicator_black.png";
    
    resources["shop_brick_at"] = "buttons/shop_brick_at.png";
    resources["shop_kielnia_indicator_white"] = "buttons/shop_kielnia_indicator_white.png";
    resources["shop_kielnia_indicator_black"] = "buttons/shop_kielnia_indicator_black.png";
    
    resources["shop_removeads"] = "buttons/shop_removeads.png";
    resources["obstacle_laser_left"] = "obstacles/laser_left.png";
    resources["obstacle_laser_center"] = "obstacles/laser_center.png";
    resources["obstacle_laser_right"] = "obstacles/laser_right.png";
    
    resources["obstacle_switch_left"] = "obstacles/switch_button_left.png";
    resources["obstacle_switch_right"] = "obstacles/switch_button_right.png";
    resources["obstacle_switch_green"] = "obstacles/switch_green.png";
    resources["obstacle_switch_red"] = "obstacles/switch_red.png";
    
    resources["shop_line_black"] = "buttons/shop_line_black.png";
    resources["shop_line_white"] = "buttons/shop_line_white.png";
    
    
    
    resources["shop_locked_black"] = "buttons/shop_locked_black.png";
    resources["shop_locked_white"] = "buttons/shop_locked_white.png";
    resources["shop_current_black"] = "buttons/shop_current_black.png";
    resources["shop_current_white"] = "buttons/shop_current_white.png";
    resources["shop_use_black"] = "buttons/shop_use_black.png";
    resources["shop_use_white"] = "buttons/shop_use_white.png";
    
    resources["popup_main"] = "buttons/popup_main.png";
    resources["popup_cancel"] = "buttons/popup_cancel.png";
    resources["popup_buy"] = "buttons/popup_buy.png";
    
    
    resources["shop_buy_black"] = "buttons/shop_buy_black.png";
    resources["shop_buy_white"] = "buttons/shop_buy_white.png";
    
    resources["shop_kielnia20_black"] = "buttons/shop_kielnia20_black.png";
    resources["shop_kielnia20_white"] = "buttons/shop_kielnia20_white.png";
    
    
    resources["shop_kielnia10_black"] = "buttons/shop_kielnia10_black.png";
    resources["shop_kielnia10_white"] = "buttons/shop_kielnia10_white.png";
    
    resources["shop_kielnia50_black"] = "buttons/shop_kielnia50_black.png";
    resources["shop_kielnia50_white"] = "buttons/shop_kielnia50_white.png";
    
    resources["shop_kielnia5_black"] = "buttons/shop_kielnia5_black.png";
    resources["shop_kielnia5_white"] = "buttons/shop_kielnia5_white.png";
    
    resources["icon_star_collect_white"] = "buttons/star_white.png";
    resources["icon_star_collect_black"] = "buttons/star_black.png";
    
    resources["obstacle_finishline"] = "obstacles/finish_line.png";
    
    resources["effect_brick_destroy"] = "sound/effect/brick_destroy.mp3";
    resources["effect_star"] = "sound/effect/star.mp3";
    resources["effect_laseroff_1"] = "sound/effect/laser_1.mp3";
    resources["effect_laseroff_2"] = "sound/effect/laser_2.mp3";
    resources["effect_laseroff_3"] = "sound/effect/laser_3.mp3";
    resources["effect_blackout"] = "sound/effect/blackout.mp3";
    resources["effect_gravity"] = "sound/effect/gravity.mp3";
    resources["effect_lvlcompleted"] = "sound/effect/level_completed.mp3";
    resources["effect_melting"] = "sound/effect/melting.mp3";
    resources["effect_brickunlocked"] = "sound/effect/brick_unlocked.mp3";
    resources["effect_chapterunlocked"] = "sound/effect/chapter_unlocked.mp3";
    resources["effect_teleport_in"] = "sound/effect/teleport_in.mp3";
    resources["effect_teleport_out"] = "sound/effect/teleport_out.mp3";
    resources["effect_denied"] = "sound/effect/denied.mp3";
    resources["effect_click"] = "sound/effect/click.mp3";
    
    resources["obstacle_teleport_in_3"] = "obstacles/teleport_in_3.png";
    resources["obstacle_teleport_in_4"] = "obstacles/teleport_in_4.png";
    resources["obstacle_teleport_in_6"] = "obstacles/teleport_in_6.png";
    
    resources["obstacle_teleport_out_3"] = "obstacles/teleport_out_3.png";
    resources["obstacle_teleport_out_4"] = "obstacles/teleport_out_4.png";
    resources["obstacle_teleport_out_6"] = "obstacles/teleport_out_6.png";
    
    resources["melting_obstacle_3"] = "obstacles/melting_obstacle_3.png";
    resources["melting_obstacle_4"] = "obstacles/melting_obstacle_4.png";
    resources["melting_obstacle_6"] = "obstacles/melting_obstacle_6.png";
    
    resources["obstacle_blackout"] = "obstacles/blackout.png";
    resources["obstacle_bullet"] = "obstacles/bullet.png";
    auto themes = ThemeManager::getInstance()->getThemes();
    int i = 1;
   // auto fu = cocos2d::FileUtils::getInstance();
   // std::string writablePath = fu->getWritablePath();
    
    
    for(const auto& theme: themes)
    {
        auto codename = theme.getCodeName();
        /*if(i > 1)
        {
            resources["music_" + codename] = writablePath + codename + ".mp3";
            CCLOG("h3h3h3h3 %s", resources["music_" + codename].c_str());
        }
        else
        {
            resources["music_" + codename] = "sound/music/" + codename + ".mp3";
        }*/
    
        resources["background_" + codename] = "themes/" + codename + "/background.png";
        resources["icon_" + codename + "_play"] = "themes/" + codename + "/play_button.png";
        resources["icon_" + codename + "_replay"] = "themes/" + codename + "/replay_button.png";
        resources["thumbnail_" + codename + "_unlocked"] = "themes/" + codename + "/thumbnail-unlocked.png";
        resources["thumbnail_" + codename + "_background"] = "themes/" + codename + "/thumbnail-background.png";
        if(i > 1)
        {
            resources["thumbnail_" + codename + "_locked"] = "themes/" + codename + "/thumbnail-locked.png";
            resources["thumbnail_" + codename + "_unlockable"] = "themes/" + codename + "/thumbnail-unlockable.png";
        }


        resources["obstacle_" + codename + "_left"] = "themes/" + codename + "/obstacle_left.png";
        resources["obstacle_" + codename + "_right"] = "themes/" + codename + "/obstacle_right.png";
        resources["obstacle_" + codename + "_center"] = "themes/" + codename + "/obstacle_center.png";
        
        if(i > 3)
        {
            resources["obstacle_" + codename + "_vert_down"] = "themes/" + codename + "/obstacle_vert_down.png";
            resources["obstacle_" + codename + "_vert_center"] = "themes/" + codename + "/obstacle_vert_center.png";
            resources["obstacle_" + codename + "_vert_up"] = "themes/" + codename + "/obstacle_vert_up.png";
        }
        i++;
    }
    
    for(int i = 1; i <= 6; i++)
    {
        resources["icon_number_finished_black_" + cocos2d::StringUtils::format("%d", i) ] = "buttons/numbers/" + cocos2d::StringUtils::format("%d", i) + "-finished-black.png";
        resources["icon_number_toplay_black_" + cocos2d::StringUtils::format("%d", i) ] = "buttons/numbers/" + cocos2d::StringUtils::format("%d", i) + "-toplay-black.png";
        
        resources["icon_number_finished_white_" + cocos2d::StringUtils::format("%d", i) ] = "buttons/numbers/" + cocos2d::StringUtils::format("%d", i) + "-finished-white.png";
        resources["icon_number_toplay_white_" + cocos2d::StringUtils::format("%d", i) ] = "buttons/numbers/" + cocos2d::StringUtils::format("%d", i) + "-toplay-white.png";
    }
    
    
    /*auto sm = SkinManager::getInstance();
    const auto& skins = sm->getSkins();
    for(const auto& skin : skins)
    {
        resources["skin_" + skin.getCodeName() + "_left"] = skin.getLeftPath();
        resources["skin_" + skin.getCodeName() + "_right"] = skin.getRightPath();
        resources["skin_" + skin.getCodeName() + "_icon"] = skin.getIconPath();
    }*/
    
    resources["icon_number_locked_black"] = "buttons/numbers/locked_black.png";
    resources["icon_number_locked_white"] = "buttons/numbers/locked_white.png";
    
    resources["icon_progressbar_filled_black"] = "buttons/progressbar_filled_black.png";
    resources["icon_progressbar_filled_white"] = "buttons/progressbar_filled_white.png";
    resources["icon_progressbar_stroke_black"] = "buttons/progressbar_stroke_black.png";
    resources["icon_progressbar_stroke_white"] = "buttons/progressbar_stroke_white.png";
    resources["waitscreen_black"] = "buttons/waitscreen_black.png";
    resources["waitscreen_white"] = "buttons/waitscreen_white.png";
    resources["icon_progressball_black"] = "buttons/progressball_black.png";
    resources["icon_progressball_white"] = "buttons/progressball_white.png";
    resources["watch_ad"] = "buttons/watchad.png";
    
    
    resources["tutorial_normal_first"] = "ui/tutorial/normal_first.png";
    resources["tutorial_normal_second"] = "ui/tutorial/normal_second.png";
    resources["tutorial_normal_third"] = "ui/tutorial/normal_third.png";
    resources["tutorial_normal_last"] = "ui/tutorial/normal_last.png";
    resources["tutorial_next_black"] = "ui/tutorial/next_black.png";
    resources["tutorial_next_white"] = "ui/tutorial/next_white.png";
    resources["tutorial_letstry_black"] = "ui/tutorial/letstry_black.png";
    resources["tutorial_letstry_white"] = "ui/tutorial/letstry_white.png";
    
    resources["tutorial_force_first"] = "ui/tutorial/force_first.png";
    resources["tutorial_force_second"] = "ui/tutorial/force_second.png";
    resources["tutorial_force_third"] = "ui/tutorial/force_third.png";
    resources["tutorial_force_fourth"] = "ui/tutorial/force_fourth.png";
    resources["tutorial_force_last"] = "ui/tutorial/force_last.png";
    
    
    resources["tutorial_normal_dots_1"] = "ui/tutorial/normal_dots_1.png";
    resources["tutorial_normal_dots_2"] = "ui/tutorial/normal_dots_2.png";
    
    resources["tutorial_force_dots_1"] = "ui/tutorial/force_dots_1.png";
    resources["tutorial_force_dots_2"] = "ui/tutorial/force_dots_2.png";
    resources["tutorial_force_dots_3"] = "ui/tutorial/force_dots_3.png";
    resources["tutorial_force_dots_4"] = "ui/tutorial/force_dots_4.png";
    
    
    resources["tutorial_desert"] = "ui/tutorial/desert.png";
    resources["tutorial_space"] = "ui/tutorial/space.png";
    resources["tutorial_western"] = "ui/tutorial/western.png";
    resources["tutorial_snowland"] = "ui/tutorial/snowland.png";
    resources["tutorial_graveyard"] = "ui/tutorial/graveyard.png";
    resources["tutorial_mouth"] = "ui/tutorial/mouth.png";
    
    resources["reward_chapter_unlocked"] = "ui/reward/chapter_unlocked.png";
    resources["reward_chapter_info"] = "ui/reward/chapter_info.png";
    
    resources["reward_brick_unlocked"] = "ui/reward/brick_unlocked.png";
    resources["reward_brick_box"] = "ui/reward/brick_box.png";
    resources["reward_guess"] = "ui/reward/brick_guess.png";
    
    
    for(int i = 0; i < 4; i++)
    {
        resources[cocos2d::StringUtils::format("lvlmenu_stars_%d_black", i)] = cocos2d::StringUtils::format("ui/lvlmenu/stars_%d_black.png", i);
        resources[cocos2d::StringUtils::format("lvlmenu_stars_%d_white", i)] = cocos2d::StringUtils::format("ui/lvlmenu/stars_%d_white.png", i); 
    }
    
    // to do SH BUTTON tutoriale
    
    resources["kielnia_popup_body"] = "ui/kielnia/popup_body.png";
    resources["kielnia_popup_shine"] = "ui/kielnia/popup_shine.png";
    resources["kielnia_popup_timer"] = "ui/kielnia/popup_timer.png";

    resources["kielnia_popup_sure"] = "ui/kielnia/popup_sure.png";
    
    resources["obstacle_bacteriablue"] = "obstacles/bacteria_1.png";
    resources["obstacle_bacteriapink"] = "obstacles/bacteria_2.png";
    resources["obstacle_bacteriagreen"] = "obstacles/bacteria_3.png";
    
    resources["shop_question_black"] = "buttons/shop_question_black.png";
    resources["shop_question_white"] = "buttons/shop_question_white.png";
    
    resources["shop_restore_white"] = "buttons/shop_restore_white.png";
    resources["shop_restore_black"] = "buttons/shop_restore_black.png";

    return resources;
}
