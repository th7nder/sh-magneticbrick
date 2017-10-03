//
//  Level.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 14/03/2017.
//
//

#include "Level.hpp"
USING_NS_CC;

// a lot of shit to dooooooooooo
const double kSecondsPerUpdate = 1.0f / 40.0f;



Level::Level() : gameHandler(nullptr), world(nullptr), accumulator(0.0), currentThemeId(0), currentLevelId(0), currentTime(0), timeBetweenObstacles(0.6), lastObstacleTime(0), lastObstacleY(2000.0), player(nullptr), map(nullptr), lastSpawnTime(0), lastDeleteTime(0), requestUpdatePlayerSpacing(false), tutorialPlayer(nullptr)
{
    this->scheduleUpdate();
    stopped = false;
}

void Level::setStopped(bool var)
{
    stopped = var;
}

bool Level::getStopped() const
{
    return stopped;
}


Level::~Level()
{
    unscheduleUpdate();
    delete world;
}

Level* Level::create(GameHandler* handler)
{
    self* ret = new (std::nothrow) self();
    if (ret && ret->init(handler))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void Level::resetRandomBackground()
{
    lastObstacleY = 2000.0;
    gameHandler->setCurrentPlayerSpeed(Globals::backgroundSpeed);
    if(levelObjects.size())
    {
        for(const auto& obj : levelObjects)
        {
            obj->release();
        }
    }
    levelObjects.clear();


}
bool Level::init(GameHandler *handler)
{
    if(!super::init()) return false;
    gameHandler = handler;
    resetRandomBackground();
    createPhysicsWorld();
    
    return true;
}

void Level::createPhysicsWorld()
{
    world = new b2World(b2Vec2(0, 0));
    world->SetContactListener(this);
    world->SetContinuousPhysics(true);
    world->SetAllowSleeping(true);
    
#if defined DEBUG_LAYER
    gameHandler->createDebugLayer(world);
#endif
    

}




void Level::update(float dt)
{
    if(stopped) return;
    auto gameState = gameHandler->getGameState();
    if(gameState != GameHandler::GameState::UI && gameState != GameHandler::GameState::Playing && gameState != GameHandler::GameState::Tutorial)
    {
        accumulator = 0;
        return;
    }

    
    currentTime += dt;
    accumulator += dt;
    
    
    if(!player)
    {
        return;
    }
    
    
    // rewrite
    if(unsigned long size = levelObjects.size())
    {
        auto obj = levelObjects.back();
        while(obj->getPositionY() + getPositionY() < 1136 + obj->getContentSize().height)
        {
            int z = obj->getZ();
            if(z != -1)
            {
                addChild(obj, obj->getZ());
            }
            else
            {
                extrasContainer->addChild(obj);
            }

            //obj->release();
            levelObjects.pop_back();
            //obj->launch();
            
            size--;
            if(!size)
            {
                break;
            }
            obj = levelObjects.back();
            
            CCLOG("creating new");
        }
            
    }
    



    while (accumulator >= kSecondsPerUpdate)
    {

        // fix me
        for(const auto& child : _children)
        {
            auto levelObject = dynamic_cast<DynamicLevelObject*>(child);
            if(levelObject != nullptr)
            {
                levelObject->savePreviousStates();
            }
            

        }
        
        

        
        accumulator -= kSecondsPerUpdate;
        world->Step(kSecondsPerUpdate, 8, 1);
        world->ClearForces();
        
    }
    


    std::vector<LevelObject*> toRemove;

    const float alpha = accumulator / kSecondsPerUpdate;
    // fix me

    int i = 0;
    for(const auto& child : _children)
    {
        
        auto levelObject = dynamic_cast<LevelObject*>(child);
       /* if(levelObject != nullptr && levelObject != levelFollower && (levelObject->getPositionY() + getPositionY()  < -levelObject->getContentSize().height))
        {
            CCLOG("clearing lO %s %p %d", levelObject->getDescription().c_str(), levelObject, i);
            toRemove.push_back(levelObject);
        }*/
        
        auto dynamicLevelObject = dynamic_cast<DynamicLevelObject*>(child);
        if(dynamicLevelObject != nullptr)
        {
            dynamicLevelObject->interpolate(alpha);
        }
    }
    
    
    if(unsigned long size = toRemove.size())
    {
        do
        {
            auto obj = toRemove.back();
            toRemove.pop_back();
            obj->removeFromParent();
            delete obj;
            
            size--;
        } while(size > 0);
    }
    
}

void Level::BeginContact(b2Contact *contact)
{
    if(gameHandler->getGameState() != GameHandler::GameState::Playing)
    {
        return;
    }
    
    b2Body* aBody = contact->GetFixtureA()->GetBody();
    b2Body* bBody = contact->GetFixtureB()->GetBody();
    LevelObject* a = static_cast<LevelObject*>(aBody->GetUserData());
    LevelObject* b = static_cast<LevelObject*>(bBody->GetUserData());
    
    if((a->OnContactBegin(b, aBody) || b->OnContactBegin(a, bBody)))
    {
        CCLOG("omg: %s, omg: %s", a->getDescription().c_str(), b->getDescription().c_str());
        
        return;
        gameHandler->setGameState(GameHandler::GameState::WinAfter);
        player->dieAnimation();
        auto seq = Sequence::create(CallFunc::create([this](){this->gameHandler->onPlayerDeath(); }),nullptr);
        runAction(seq);

    }
}

void Level::EndContact(b2Contact *contact)
{
    if(gameHandler->getGameState() != GameHandler::GameState::Playing)
    {
        return;
    }
    
    b2Body* aBody = contact->GetFixtureA()->GetBody();
    b2Body* bBody = contact->GetFixtureB()->GetBody();
    LevelObject* a = static_cast<LevelObject*>(aBody->GetUserData());
    LevelObject* b = static_cast<LevelObject*>(bBody->GetUserData());
    
    a->OnContactEnd(b);
    b->OnContactEnd(a);
}

bool Level::reload()
{
    return load(currentThemeId, currentLevelId);
}

bool Level::loadNext(int lid)
{
    return load(currentThemeId, lid);
}


std::string Level::getPath(int themeId, int levelId)
{
    const auto codename = gameHandler->getLastTheme().getCodeName();
    std::string loadPath = "maps/" + codename+ "/" + codename + "_";
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << levelId;
    loadPath += ss.str() + ".tmx";
    return loadPath;
}

std::string Level::getExtrasPath(int themeId, int levelId)
{
    const auto codename = gameHandler->getLastTheme().getCodeName();
    std::string loadPath = "maps/" + codename+ "/extra/" + codename + "_";
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << levelId;
    loadPath += ss.str() + ".extras";
    return loadPath;
}


bool Level::load(int themeId, int levelId)
{

    gameHandler->setBulletTime(false);
    gameHandler->setBlackout(false);
    gameHandler->setGravity(false);
    gameHandler->setInfection(false);
    

    removeAllChildrenWithCleanup(true);
    player = nullptr;
    
    extrasContainer = Node::create();
    addChild(extrasContainer, -1);
    

    
    if(levelObjects.size())
    {
        for(const auto& obj : levelObjects)
        {
            obj->release();
        }
    }
    levelObjects.clear();

    if(currentThemeId != themeId || currentLevelId != levelId)
    {
        if(map != nullptr)
        {
            CC_SAFE_RELEASE_NULL(map);
        }
        map = TMXTiledMap::create(getPath(themeId, levelId));
        map->retain();
    }
    
    
    
    currentThemeId = themeId;
    currentLevelId = levelId;
    
    const auto lastThemeCodename = "obstacle_" +  gameHandler->getLastTheme().getCodeName();
    HorizontalObstacle::leftTexture = Globals::resources[lastThemeCodename + "_left"];
    HorizontalObstacle::centerTexture = Globals::resources[lastThemeCodename + "_center"];
    HorizontalObstacle::rightTexture = Globals::resources[lastThemeCodename + "_right"];
    MovingObstacle::leftTexture = Globals::resources[lastThemeCodename + "_left"];
    MovingObstacle::centerTexture = Globals::resources[lastThemeCodename + "_center"];
    MovingObstacle::rightTexture = Globals::resources[lastThemeCodename + "_right"];
    const std::string laserName = "obstacle_laser";
    Laser::leftTexture = Globals::resources[laserName + "_left"];
    Laser::centerTexture = Globals::resources[laserName + "_center"];
    Laser::rightTexture = Globals::resources[laserName + "_right"];
    const std::string vertName = "obstacle_" +  gameHandler->getLastTheme().getCodeName();
    VerticalObstacle::downTexture = Globals::resources[vertName + "_vert_down"];
    VerticalObstacle::centerTexture = Globals::resources[vertName + "_vert_center"];
    VerticalObstacle::upTexture = Globals::resources[vertName + "_vert_up"];

    auto objectGroups = map->getObjectGroups();
    for (auto& objectGroup : objectGroups)
    {
        auto objects = objectGroup->getObjects();
        auto className = objectGroup->getGroupName();
        for (auto& object : objects)
        {
            auto properties = object.asValueMap();
            auto type = properties.at("type");
            if (!type.isNull())
            {
                addObject(type.asString().c_str(), properties);
            }
            else
            {
                addObject(className.c_str(), properties);
            }
            
        }
    }
    
    loadExtras(themeId, levelId);
    
    
    std::sort(levelObjects.begin(), levelObjects.end(), [](const LevelObject* s1, const LevelObject* s2) -> bool {
        return s1->getPositionY() - (s1->getContentSize().height / 2) > s2->getPositionY() - (s2->getContentSize().height / 2);
    });
    

    return true;
}


void Level::loadExtras(int themeId, int levelId)
{
   
    if(themeId > 6 && themeId != 9) return;
    
    auto extrasFile = FileUtils::getInstance()->getStringFromFile(getExtrasPath(themeId, levelId));
    
    std::istringstream inputstream(extrasFile);
    std::string line;
    std::vector<std::string> exploded;

    while(std::getline(inputstream, line))
    {
        exploded = explode(line, ';');
        ValueMap props;
        props["type"] = exploded[0];
        props["orientation"] = exploded[1];
        props["width"] = exploded[2];
        props["height"] = exploded[3];
        props["x"] = exploded[4];
        props["y"] = exploded[5];
        addObject(exploded[0].c_str(), props);
    }
    

    
}

LevelObject* Level::addObject(std::string className, ValueMap& properties, bool random)
{
    LevelObject* o = nullptr;
    bool push = false;
    if(className == "Player")
    {

        CCLOG("creating player");
        walls = (Walls*)addObject("Walls", properties);
        levelFollower = (LevelFollower*)addObject("LevelFollower", properties);
        auto destroyer = (Destroyer*)addObject("Destroyer", properties);
        player = new Player(gameHandler->getCurrentSkin(), levelFollower, walls);
        o = player;
    }
    else if(className == "Destroyer")
    {
        // to do destruction of destroyer
        o = new Destroyer();
        random = true;
    }
    else if(className == "Walls")
    {
        o = new Walls();
        random = true;
    }
    else if(className == "LevelFollower")
    {
        o = new LevelFollower();
        random = true;
    }
    else if(className == "HorizontalObstacle")
    {
        o = new HorizontalObstacle();
    }
    else if(className == "Switch")
    {
        o = new Switch();
    }
    else if(className == "Laser")
    {
        o = new Laser();
    }
    else if(className == "Star")
    {
        o = new Star();
    }
    else if(className == "MovingObstacle")
    {
        o = new MovingObstacle();
        push = true;
    }
    else if(className == "FinishLine")
    {
        o = new FinishLine();
    }
    else if(className == "VerticalObstacle")
    {
        o = new VerticalObstacle();
    }
    else if(className == "TeleportIn")
    {
        o = new TeleportIn();
    }
    else if(className == "TeleportOut")
    {
        o = new TeleportOut();
    }
    else if(className == "MeltingObstacle")
    {
        o = new MeltingObstacle();
        push = true;
    }
    /*else if(className == "TriggerMelting")
    {
        o = new TriggerMelting();
    }*/
    else if(className == "BulletTimeStart")
    {
        o = new BulletTimeStart();
    }
    else if(className == "BulletTimeStop")
    {
        o = new BulletTimeEnd();
        push = true;
    }
    else if(className == "Bullet")
    {
        o = new Bullet();
       // random = true;
    }
    else if(className == "BlackoutStart")
    {
        o = new BlackoutStart();
    }
    else if(className == "BlackoutStop")
    {
        o = new BlackoutStop();
    }
    else if(className == "Gravity")
    {
        o = new Gravity();
    }
    else if(className == "BacteriaBlue")
    {
        o = new BacteriaBlue();
        //random = true;
    }
    else if(className == "BacteriaPink")
    {
        o = new BacteriaPink();
        //random = true;
    }
    else if(className == "BacteriaGreen")
    {
        o = new BacteriaGreen();
        //random = true;
    }
    else if(className == "InfectionStart")
    {
        o = new InfectionStart();
    }
    else if(className == "InfectionStop")
    {
        o = new InfectionStop();
        push = true;
    }
    /*else if(className == "CSESmall")
    {
        o = new CSESmall();
    }
    else if(className == "CSEMedium")
    {
        o = new CSEMedium();
    }
    else if(className == "CSEBig")
    {
        o = new CSEBig();
    }
    else if(className == "CSEBarrier")
    {
        o = new CSEBarrier();
    }
    else if(className == "CSEBall")
    {
        o = new CSEBall();
    }
    else if(className == "JEDouble")
    {
        o = new JEDouble();
    }
    else if(className == "JETriple")
    {
        o = new JETriple();
    }
    else if(className == "JEReversed")
    {
        o = new JEReversed();
    }
    else if(className == "DESkull")
    {
        o = new DESkull();
    }
    else if(className == "DECactus")
    {
        o = new DECactus();
    }
    else if(className == "CECometBlue")
    {
        o = new CECometBlue();
    }
    else if(className == "CECometRed")
    {
        o = new CECometRed();
    }
    else if(className == "CEAlienRed")
    {
        o = new CEAlienRed();
    }
    else if(className == "CEAlienGreen")
    {
        o = new CEAlienGreen();
    }
    else if(className == "CEAlienBlue")
    {
        o = new CEAlienBlue();
    }
    else if(className == "WEBoot")
    {
        o = new WEBoot();
    }
    else if(className == "WEHat")
    {
        o = new WEHat();
    }
    else if(className == "WEPistol")
    {
        o = new WEPistol();
    }
    else if(className == "SESnowflakeBig")
    {
        o = new SESnowflakeBig();
    }
    else if(className == "SESnowflakeSmall")
    {
        o = new SESnowflakeSmall();
    }
    else if(className == "HETrident")
    {
        o = new HETrident();
    }
    else if(className == "HESkull")
    {
        o = new HESkull();
    }
    else if(className == "HETail")
    {
        o = new HETail();
    }
    else if(className == "UEFishOrange")
    {
        o = new UEFishOrange();
    }
    else if(className == "UEFishGreen")
    {
        o = new UEFishGreen();
    }
    else if(className == "UEFishRed")
    {
        o = new UEFishRed();
    }
    else if(className == "UETentacle")
    {
        o = new UETentacle();
    }
    else if(className == "Parrot")
    {
        o = new Parrot();
    }*/
    
    
    
    
    if( o != nullptr )
    {
        o->setProperties(properties);
        o->addSprite();
        o->initPhysics(world);
    
        if(o->isDynamic())
        {
            dynamicLevelObjects.push_back(static_cast<DynamicLevelObject*>(o));
        }
        
        
        if(!random && (o->getPositionY() > 1136 * 1.5 || push))
        {
            levelObjects.push_back(o);
        }
        else
        {
            addChild(o, o->getZ());
            Destroyer* d;
            if((d = dynamic_cast<Destroyer*>(o)) != nullptr)
            {
                d->launch();
            }
                
        }
    }
    
    return o;
}

void Level::resetPlayerPosY()
{
    player->resetSpriteY();
}


void Level::createRandomObstacle()
{
    return;
    ValueMap props;
    float nextY = lastObstacleY + random(500.0f, 800.f);
    const float centerWidth = 2 * 108.0f + random(0.0f, 1080.0f - 8.0f * 108.0f); // 702 = 1080 - 3.5 * 108 | minimal size, space and margin
    const float maxX = 1080.0f - centerWidth; // - minimal width of obstacle
    float x = random(0.0f, maxX);

    

    props["width"] = centerWidth;
    props["height"] = 54.0;
    props["x"] = x;
    props["y"] = nextY;
    props["physics"] = false;


    addObject("HorizontalObstacle", props, true);
    if(x > 4 * 108) // minimal size + some margin
    {
        ValueMap secondProps;
        const float secondWidth = 2 * 108.0f + random(0.0f, x - 108.0f);
        const float secondMaxX = x - 108.0 - secondWidth;
        const float secondX = random(0.0f, secondMaxX);
        

        secondProps["width"] = secondWidth;
        secondProps["height"] = 54.0f;
        secondProps["x"] = secondX;
        secondProps["y"] = nextY;
        secondProps["physics"] = false;
        
        addObject("HorizontalObstacle", secondProps, true);
    }
    if(1080.0 - (x + centerWidth) > 4 * 108)
    {
        ValueMap thirdProps;
        const float thirdWidth = 2 * 108.0f + random(0.0f, 1080.0f - (x + centerWidth) - 108.0f);
        const float thirdMaxX = 1080.0f - thirdWidth;
        const float thirdX = random(x + 108.0f, thirdMaxX);
        

        thirdProps["width"] = thirdWidth;
        thirdProps["height"] = 54.0f;
        thirdProps["x"] = thirdX;
        thirdProps["y"] = nextY;
        thirdProps["physics"] = false;
        addObject("HorizontalObstacle", thirdProps, true);
    }
    
    lastObstacleY = nextY;
    
}


void Level::updatePlayerPos()
{
    requestUpdatePlayerSpacing = true;
}

bool Level::isPlayerInTeleport()
{
    return false;
    //return player->isInTeleport();
}
