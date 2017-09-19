//
//  Level.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 14/03/2017.
//
//

#include "Level.hpp"
USING_NS_CC;


const double kSecondsPerUpdate = 1.0f / 40.0f;



Level::Level() : gameHandler(nullptr), world(nullptr), accumulator(0.0), currentThemeId(0), currentLevelId(0), currentTime(0), timeBetweenObstacles(0.6), lastObstacleTime(0), lastObstacleY(2000.0), player(nullptr), map(nullptr), lastSpawnTime(0), lastDeleteTime(0), requestUpdatePlayerSpacing(false), tutorialPlayer(nullptr)
{
    this->scheduleUpdate();
    LevelObject::ownVisibleSize = Director::getInstance()->getVisibleSize();
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
    
    
 

    
    
    const auto children = getChildren();
    if(gameState == GameHandler::GameState::UI)
    {
        if(currentTime - lastObstacleTime >= timeBetweenObstacles)
        {
            lastObstacleTime = currentTime;
            createRandomObstacle();
        }
        
        gameHandler->onPlayerUpdate(dt, -466.0);
        

        for(const auto& child : children)
        {
            auto levelObject = dynamic_cast<LevelObject*>(child);
            if(levelObject != nullptr)
            {
                if(levelObject->remove || (levelObject->getPositionY() + getPositionY() < -levelObject->getContentSize().height))
                {
                    levelObject->removeFromParentAndCleanup(true);
                }
            }
        }
        
        return;
    }
    
    
    if(!player)
    {
        return;
    }
    
    
#if !defined DOWNLOAD_MAPS
    if(player != nullptr)
    {
        gameHandler->onPlayerUpdate(dt, player->getPositionY());
    }
#endif

    
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


            obj->release();
            levelObjects.pop_back();
            obj->launch();
            
            size--;
            if(!size)
            {
                break;
            }
            obj = levelObjects.back();
        }
            
    }
    


    if(requestUpdatePlayerSpacing)
    {
        player->updateBricksSpacing();
        requestUpdatePlayerSpacing = false;
    }

    while (accumulator >= kSecondsPerUpdate)
    {

        for(const auto& child : children)
        {
            if(tutorialPlayer != nullptr)
            {
                tutorialPlayer->savePreviousStates();
            }
            auto levelObject = dynamic_cast<LevelObject*>(child);
            if(levelObject != nullptr && levelObject != walls)
            {
                if(levelObject != levelFollower && (levelObject->remove || levelObject->getPositionY() + getPositionY()  < -levelObject->getContentSize().height))
                {
                    levelObject->removeFromParentAndCleanup(true);
                }
                else
                {
                    levelObject->savePreviousStates();
                }
            }
        }

        
        accumulator -= kSecondsPerUpdate;
        world->Step(kSecondsPerUpdate, 8, 1);
        world->ClearForces();
        
    }
  

    
    const float alpha = accumulator / kSecondsPerUpdate;
    for(const auto& child : children)
    {
        auto levelObject = dynamic_cast<LevelObject*>(child);
        if(levelObject != nullptr)
        {
            levelObject->interpolate(alpha);
        }
    }
    
    if(tutorialPlayer != nullptr)
    {
        tutorialPlayer->interpolate(alpha);
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
        gameHandler->setGameState(GameHandler::GameState::WinAfter);
        player->die();
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


void Level::downloadMap(int themeId, int levelId)
{
    stopped = true;
    downloadingThemeId = themeId;
    downloadingLevelId = levelId;
    std::string url = StringUtils::format("https://skyhorn.tech/apps/magneticbrick/maps/%s_0%d.tmx", gameHandler->getTheme(themeId).getCodeName().c_str(), levelId);
    network::HttpRequest* request = new cocos2d::network::HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(Level::onHttpMapDownloaded, this));
    request->setTag(StringUtils::format("%s_0%d.tmx", gameHandler->getTheme(themeId).getCodeName().c_str(), levelId));
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}


void Level::onHttpMapDownloaded(network::HttpClient *pSender, network::HttpResponse *pResponse)
{
    CCLOG("sth happened %ld", pResponse->getResponseCode());
    if(pResponse->getResponseCode() != 200) return;
    
    std::string writablePath = FileUtils::getInstance()->getInstance()->getWritablePath();
    writablePath.append(pResponse->getHttpRequest()->getTag());
    CCLOG("writablePath: %s", writablePath.c_str());
    std::vector<char> *buffer = pResponse->getResponseData();

    std::FILE* f = std::fopen(writablePath.c_str(), "wb");
    std::fwrite(buffer->data(), sizeof((*buffer)[0]), buffer->size(), f);
    std::fclose(f);
    

     
    int themeId = downloadingThemeId;
    int levelId = downloadingLevelId;
    if(currentThemeId != themeId || currentLevelId != levelId)
    {
        if(map != nullptr)
        {
            CC_SAFE_RELEASE_NULL(map);
        }
        map = TMXTiledMap::create(writablePath);
        map->retain();
    }
    
    
    currentThemeId = themeId;
    currentLevelId = levelId;
    
    
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
    
    stopped = false;
    
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
#if defined DOWNLOAD_MAPS
    downloadMap(themeId, levelId);
#else

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
    
#endif

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

        walls = (Walls*)addObject("Walls", properties);
        levelFollower = (LevelFollower*)addObject("LevelFollower", properties);
        player = Player::create(gameHandler, walls, levelFollower);
        o = player;
    }
    else if(className == "Walls")
    {
        o = Walls::create(gameHandler);
        random = true;
    }
    else if(className == "LevelFollower")
    {
        o = LevelFollower::create(gameHandler);
        random = true;
    }
    else if(className == "HorizontalObstacle")
    {
        o = HorizontalObstacle::create(gameHandler);
    }
    else if(className == "Switch")
    {
        o = Switch::create(gameHandler);
    }
    else if(className == "Laser")
    {
        o = Laser::create(gameHandler);
    }
    else if(className == "Star")
    {
        o = Star::create(gameHandler);
    }
    else if(className == "MovingObstacle")
    {
        o = MovingObstacle::create(gameHandler);
        push = true;
    }
    else if(className == "FinishLine")
    {
        o = FinishLine::create(gameHandler);
    }
    else if(className == "VerticalObstacle")
    {
        o = VerticalObstacle::create(gameHandler);
    }
    else if(className == "TeleportIn")
    {
        o = TeleportIn::create(gameHandler);
    }
    else if(className == "TeleportOut")
    {
        o = TeleportOut::create(gameHandler);
    }
    else if(className == "MeltingObstacle")
    {
        o = MeltingObstacle::create(gameHandler);
        push = true;
    }
    /*else if(className == "TriggerMelting")
    {
        o = TriggerMelting::create(gameHandler);
    }*/
    else if(className == "BulletTimeStart")
    {
        o = BulletTimeStart::create(gameHandler);
    }
    else if(className == "BulletTimeStop")
    {
        o = BulletTimeEnd::create(gameHandler);
        push = true;
    }
    else if(className == "Bullet")
    {
        o = Bullet::create(gameHandler);
       // random = true;
    }
    else if(className == "BlackoutStart")
    {
        o = BlackoutStart::create(gameHandler);
    }
    else if(className == "BlackoutStop")
    {
        o = BlackoutStop::create(gameHandler);
    }
    else if(className == "Gravity")
    {
        o = Gravity::create(gameHandler);
    }
    else if(className == "BacteriaBlue")
    {
        o = BacteriaBlue::create(gameHandler);
        //random = true;
    }
    else if(className == "BacteriaPink")
    {
        o = BacteriaPink::create(gameHandler);
        //random = true;
    }
    else if(className == "BacteriaGreen")
    {
        o = BacteriaGreen::create(gameHandler);
        //random = true;
    }
    else if(className == "InfectionStart")
    {
        o = InfectionStart::create(gameHandler);
    }
    else if(className == "InfectionStop")
    {
        o = InfectionStop::create(gameHandler);
        push = true;
    }
    /*else if(className == "CSESmall")
    {
        o = CSESmall::create(gameHandler);
    }
    else if(className == "CSEMedium")
    {
        o = CSEMedium::create(gameHandler);
    }
    else if(className == "CSEBig")
    {
        o = CSEBig::create(gameHandler);
    }
    else if(className == "CSEBarrier")
    {
        o = CSEBarrier::create(gameHandler);
    }
    else if(className == "CSEBall")
    {
        o = CSEBall::create(gameHandler);
    }
    else if(className == "JEDouble")
    {
        o = JEDouble::create(gameHandler);
    }
    else if(className == "JETriple")
    {
        o = JETriple::create(gameHandler);
    }
    else if(className == "JEReversed")
    {
        o = JEReversed::create(gameHandler);
    }
    else if(className == "DESkull")
    {
        o = DESkull::create(gameHandler);
    }
    else if(className == "DECactus")
    {
        o = DECactus::create(gameHandler);
    }
    else if(className == "CECometBlue")
    {
        o = CECometBlue::create(gameHandler);
    }
    else if(className == "CECometRed")
    {
        o = CECometRed::create(gameHandler);
    }
    else if(className == "CEAlienRed")
    {
        o = CEAlienRed::create(gameHandler);
    }
    else if(className == "CEAlienGreen")
    {
        o = CEAlienGreen::create(gameHandler);
    }
    else if(className == "CEAlienBlue")
    {
        o = CEAlienBlue::create(gameHandler);
    }
    else if(className == "WEBoot")
    {
        o = WEBoot::create(gameHandler);
    }
    else if(className == "WEHat")
    {
        o = WEHat::create(gameHandler);
    }
    else if(className == "WEPistol")
    {
        o = WEPistol::create(gameHandler);
    }
    else if(className == "SESnowflakeBig")
    {
        o = SESnowflakeBig::create(gameHandler);
    }
    else if(className == "SESnowflakeSmall")
    {
        o = SESnowflakeSmall::create(gameHandler);
    }
    else if(className == "HETrident")
    {
        o = HETrident::create(gameHandler);
    }
    else if(className == "HESkull")
    {
        o = HESkull::create(gameHandler);
    }
    else if(className == "HETail")
    {
        o = HETail::create(gameHandler);
    }
    else if(className == "UEFishOrange")
    {
        o = UEFishOrange::create(gameHandler);
    }
    else if(className == "UEFishGreen")
    {
        o = UEFishGreen::create(gameHandler);
    }
    else if(className == "UEFishRed")
    {
        o = UEFishRed::create(gameHandler);
    }
    else if(className == "UETentacle")
    {
        o = UETentacle::create(gameHandler);
    }
    else if(className == "Parrot")
    {
        o = Parrot::create(gameHandler);
    }*/
    
    
    
    
    if( o != nullptr )
    {
        o->setProperties(properties);
        o->addSprite();
        o->initPhysics(world);


        if(!random && (o->getPositionY() > 1136 * 1.5 || push))
        {
            o->retain();
            levelObjects.push_back(o);
            //addChild(o, o->getZ());
        }
        else
        {
            addChild(o, o->getZ());
            o->launch();
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
