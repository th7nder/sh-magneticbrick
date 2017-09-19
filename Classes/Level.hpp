//
//  Level.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 14/03/2017.
//
//

#ifndef Level_hpp
#define Level_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "cocos2d.h"
#include <Box2D/Box2D.h>

#include "Globals.hpp"
#include "network/HttpClient.h"

#include "GameHandler.hpp"

#include "LevelObject.hpp"
#include "Player.hpp"
#include "HorizontalObstacle.hpp"
#include "Star.hpp"
#include "Laser.hpp"
#include "Switch.hpp"
#include "MovingObstacle.hpp"
#include "FinishLine.hpp"
#include "VerticalObstacle.hpp"
#include "TeleportIn.hpp"
#include "TeleportOut.hpp"
#include "MeltingObstacle.hpp"
#include "Walls.hpp"
#include "TriggerMelting.hpp"
#include "Bullet.hpp"
#include "BulletTimeStart.hpp"
#include "BulletTimeEnd.hpp"
#include "B2DebugDrawLayer.h"
#include "SimpleAudioEngine.h"

#include "BlackoutStart.hpp"
#include "BlackoutStop.hpp"
#include "Gravity.hpp"
#include "BacteriaBlue.hpp"
#include "BacteriaPink.hpp"
#include "BacteriaGreen.hpp"

#include "InfectionStart.hpp"
#include "InfectionStop.hpp"

#include "LevelFollower.hpp"

/*#include "CSESmall.hpp"
#include "CSEMedium.hpp"
#include "CSEBig.hpp"
#include "CSEBarrier.hpp"
#include "CSEBall.hpp"

#include "JEDouble.hpp"
#include "JETriple.hpp"
#include "JEReversed.hpp"

#include "DESkull.hpp"
#include "DECactus.hpp"

#include "CECometBlue.hpp"
#include "CECometRed.hpp"
#include "CEAlienRed.hpp"
#include "CEAlienGreen.hpp"
#include "CEAlienBlue.hpp"

#include "WEBoot.hpp"
#include "WEHat.hpp"
#include "WEPistol.hpp"


#include "SESnowflakeBig.hpp"
#include "SESnowflakeSmall.hpp"

#include "HETrident.hpp"
#include "HESkull.hpp"
#include "HETail.hpp"

#include "UEFishOrange.hpp"
#include "UEFishGreen.hpp"
#include "UEFishRed.hpp"
#include "UETentacle.hpp"

#include "Parrot.hpp"*/

class Level : public cocos2d::Node, public b2ContactListener
{
    typedef cocos2d::Node super;
    typedef Level self;
    GameHandler* gameHandler;
    
    bool requestUpdatePlayerSpacing;
    
  
    
    std::vector<LevelObject*> levelObjects;
    

    Node* extrasContainer;
    double lastSpawnTime;
    double lastDeleteTime;
    void createPhysicsWorld();
    virtual void BeginContact(b2Contact* contact) override;
    virtual void EndContact(b2Contact* contact) override;

    double currentTime;
    double accumulator;
    

    
    double lastObstacleTime;
    double timeBetweenObstacles;
    float lastObstacleY;
    virtual void update(float dt) override;
    int currentThemeId;
    int currentLevelId;
    void loadExtras(int themeId, int levelId);


    Walls* walls;
    Player* tutorialPlayer;
    LevelFollower* levelFollower;
    std::string getPath(int themeId, int levelId);
    std::string getExtrasPath(int themeId, int levelId);
    TMXTiledMap* map;
    
    int downloadingThemeId;
    int downloadingLevelId;
    
    void downloadMap(int themeId, int levelId);
    void onHttpMapDownloaded(network::HttpClient* pSender, network::HttpResponse* pResponse);
CC_CONSTRUCTOR_ACCESS:
    Level();
public:
    b2World* world;
    Player* player;
    virtual ~Level();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler);
    bool load(int themeId, int levelId);
    bool reload();
    bool loadNext(int lId);
    LevelObject* addObject(std::string className, ValueMap& properties, bool random = false);
    void createRandomBullet();
    void createRandomObstacle();
    void resetRandomBackground();
    
    CC_PROPERTY(bool, stopped, Stopped);
    
    void resetPlayerPosY();
    void updatePlayerPos();
    bool isPlayerInTeleport();
    
    void setTutorialPlayer(Player* player)
    {
        tutorialPlayer = player;
    }
};

#endif /* Level_hpp */
