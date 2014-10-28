//includes
#include "Utilities/VERSION.hpp"
#include "Utilities/Logger.hpp"
#include <iostream>
#include "MemoryBank/DataBank.hpp"
#include "MemoryBank/Level/Vector.hpp"
#include "GUI/GUIManager.hpp"
#include "Processing/GraphicsEngine.hpp"
#include "Processing/PhysicsEngine.hpp"
#include "Processing/ModModule.hpp"
#include "Processing/EventManager.hpp"
#include <conio.h>
#include <list>
#include <time.h>
#include "Utilities/util.hpp"
#include <SFML\System.hpp>


extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


// Thread Throttleling
float mLimit =  100.0; //Cycles per second
float gLimit =  100.0; //Cycles per second
float pLimit =  100.0; //Cycles per second
float mainLimit =  100.0; //Cycles per second

// Global accessors
std::list< std::list<std::string> > eventBuffer;
std::list< std::list<std::string> > taskBuffer;
std::string selectedSystem;
// pointer
DataBank*       dLink;
GUIManager*     guiLink;
GraphicsEngine* gLink;
PhysicsEngine*  pLink;
ModModule*      mLink;

//threads
sf::Thread*     gThread;
sf::Thread*     pThread;
sf::Thread*     mThread;

sf::Mutex GMutex;

void StockRegister();
void StockSettings();
void StockKeybinds();



int main ( int argc, char *argv[] )
{
    LOG::console("[Main][Info] Logger enabled");



    ////////////////////
    // 1. DataBank    //
    //                //
    // 2. GUIManager  //
    //                //
    // 3. Processing  //
    ////////////////////

    ///// 1. DataBank
    LOG::console("[Main][Info] Create Memory Mangager Instance...");
    DataBank dBank;
    dLink = &dBank;

    //App Instance
    LOG::console("[Main][Info] Generate RenderDevice(Window)...");
    sf::RenderWindow App(sf::VideoMode(1280, 720, 32), VERSION::name + " " + VERSION::version, sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    LOG::console("[Main][Info] Re-Apply view...");
    dLink->gameView = App.getDefaultView();
    dLink->gameView.move(- (App.getSize().x / 2.0),- (App.getSize().y / 2.0));
    dLink->guiView = App.getDefaultView();
    LOG::console("[Main][Info] Launch RenderLink...");
    dLink->renderWindow = &App;

    StockRegister();
    StockSettings();

    // 2. GUIManager
    LOG::console("[Main][Info] Create GUI Instance...");
    GUIManager gManager;
    guiLink = &gManager;

    // 3. Processing
    //Graphics Engine
    LOG::console("[Main][Info] Create Graphics Thread...");
    GraphicsEngine graphicsThread;
    gLink = &graphicsThread;
    LOG::console("[Main][Info] Relocate Render Thread...");
    App.setActive(false);

    //Physics Engine
    LOG::console("[Main][Info] Create Physics Thread...");
    sf::sleep(sf::seconds(0.05));
    PhysicsEngine physicsThread;
    pLink = &physicsThread;

    //Modding Module
    LOG::console("[Main][Info] Create Plugin Handler...");
    sf::sleep(sf::seconds(0.05));
    ModModule mModule;
    mLink = &mModule;

    //Event Manager
    LOG::console("[Main][Info] Create Event Manager...");
    sf::sleep(sf::seconds(0.05));
    EventManager EventMan;

    StockKeybinds();

    ////Create threads
    LOG::console("[Main][Info] Create Mod- Thread");
    sf::Thread plTHREAD(&ModModule::Run, &mModule);
    LOG::console("[Main][Info] Create Graphics- Thread");
    sf::Thread grTHREAD(&GraphicsEngine::Run, &graphicsThread);
    LOG::console("[Main][Info] Create Physics- Thread");
    sf::Thread phTHREAD(&PhysicsEngine::Run, &physicsThread);

    LOG::console("[Main][Info] Link Mod- Thread");
    mThread = &plTHREAD;
    LOG::console("[Main][Info] Link Graphics- Thread");
    gThread = &grTHREAD;
    LOG::console("[Main][Info] Link Physics- Thread");
    pThread = &phTHREAD;

    LOG::console("[Main][Info] Launch Mod- Thread");
    mThread->launch();
    LOG::console("[Main][Info] Launch Graphics- Thread");
    gThread->launch();
    LOG::console("[Main][Info] Launch Physics- Thread");
    pThread->launch();

    GMutex.lock();
    LOG::console("[Main][Info] Entering Event-Loop");
    GMutex.unlock();


    // Init Debugging
    std::list<std::string> x;
    x.push_back("delay");
    x.push_back(util::toString(dLink->settings.countResetInterval*1000));
    x.push_back("debug");
    x.push_back("countReset");
    dLink->pushTask(x);



    sf::Clock limit;
    limit.restart();
    while(App.isOpen())
    {
        GMutex.unlock();
        while(dLink->debug.tMainSleep.size() > dLink->settings.threadMeanAmount)
        {
            dLink->debug.tMainSleep.pop_front();
        }
        if(limit.getElapsedTime().asSeconds() < 1.0/mainLimit)
        {
            dLink->debug.tMainSleep.push_back((1.0/mainLimit - limit.getElapsedTime().asSeconds())*1000);
            sf::sleep(sf::seconds(1.0/mainLimit - limit.getElapsedTime().asSeconds()));
        }
        else
        {
            dLink->debug.tMainSleep.push_back(0.0);
        }

        limit.restart();

        GMutex.lock();
        sf::Event Event;
        while(App.pollEvent(Event))
        {
            EventMan.processEvent(&Event);
        }
        for(int i = dLink->softEvents.size(); i > 0; i--)
        {
            EventMan.processSoftEvent(dLink->pullEvent());
        }
        for(int i = dLink->softTasks.size(); i > 0; i--)
        {
            EventMan.processTask(dLink->pullTask());
        }
    }
    GMutex.unlock();

    printf("\n=|=|=|=|=|=|=|=|=|=|=|=|=|=\n\nThe game closed. If you see errors above, please contact the developers");
    //getchar();
    return EXIT_SUCCESS;
}

void StockRegister()
{
    //stock resources
    dLink->FontRegister   ("$_menuTitle"          , "content/stock/font/lucon.ttf");

    dLink->TextureRegister("$_dockMain"           , "content/stock/texture/gui/dock/main.png"                         );
    dLink->TextureRegister("$_dockOptions"        , "content/stock/texture/gui/dock/options.png"                      );
    dLink->TextureRegister("$_missing"            , "content/stock/texture/missing.png"                               );
    dLink->TextureRegister("$_stars"              , "content/stock/texture/stars.png"                                 );
}
void StockSettings()
{
    dLink->settings.safemode                              =  true;

    dLink->settings.threadMeanAmount                      =   40;
    dLink->settings.eventtaskMeanAmount                   =    3;
    dLink->settings.countResetInterval                    = 1.0f;

    dLink->settings.dockWidth                             =   40;


    dLink->settings.guiDockBackground                     = sf::Color(  0,  0,  0,255);
    dLink->settings.guiDockBackgroundHover                = sf::Color(  0, 64,  0,128);
    dLink->settings.guiDockBorder                         = sf::Color(  0,255,  0,255);
    dLink->settings.guiDockBorderHover                    = sf::Color(255,255,255,255);
    dLink->settings.guiDockItemBackground                 = sf::Color(  0,  0,  0,255);
    dLink->settings.guiDockItemBackgroundHover            = sf::Color( 32, 32, 32,255);
    dLink->settings.guiDockItemBorder                     = sf::Color(  0,255,  0,255);
    dLink->settings.guiDockItemBorderHover                = sf::Color(255,255,255,255);

    dLink->settings.guiMenuBorderInactive                 = sf::Color(128,128,128,128);
    dLink->settings.guiMenuBorderActive                   = sf::Color(  0,255,  0,255);
    dLink->settings.guiMenuBackgroundInactive             = sf::Color(  0,  0,  0,200);
    dLink->settings.guiMenuBackgroundActive               = sf::Color(  0,  0,  0,230);
    dLink->settings.guiMenuTitleBackgroundInactive        = sf::Color(  0,  0,  0,128);
    dLink->settings.guiMenuTitleBackgroundActive          = sf::Color(  0,  0,  0,200);
    dLink->settings.guiMenuTitleTextInactive              = sf::Color(255,255,255,128);
    dLink->settings.guiMenuTitleTextActive                = sf::Color(255,255,255,255);

    dLink->settings.guiButtonBackgroundInactive           = sf::Color( 40, 40, 40, 64);
    dLink->settings.guiButtonBackgroundActive             = sf::Color( 40, 40, 40,128);
    dLink->settings.guiButtonBackgroundHover              = sf::Color( 40, 40, 40,255);
    dLink->settings.guiButtonBackgroundClicked            = sf::Color(  0,255,  0,255);
    dLink->settings.guiButtonBorderInactive               = sf::Color( 80, 80, 80,128);
    dLink->settings.guiButtonBorderActive                 = sf::Color(  0,255,  0,128);
    dLink->settings.guiButtonBorderHover                  = sf::Color(  0,255,  0,255);
    dLink->settings.guiButtonBorderClicked                = sf::Color(255,255,255,255);
    dLink->settings.guiButtonTextInactive                 = sf::Color(255,255,255, 80);
    dLink->settings.guiButtonTextActive                   = sf::Color(255,255,255,160);
    dLink->settings.guiButtonTextHover                    = sf::Color(255,255,255,255);

    dLink->settings.guiCheckboxBackgroundInactive           = sf::Color( 40, 40, 40, 64);
    dLink->settings.guiCheckboxBackgroundActive             = sf::Color( 40, 40, 40,128);
    dLink->settings.guiCheckboxBackgroundHover              = sf::Color( 40, 40, 40,255);
    dLink->settings.guiCheckboxBackgroundChecked            = sf::Color(  0,255,  0,255);
    dLink->settings.guiCheckboxBorderInactive               = sf::Color( 80, 80, 80,128);
    dLink->settings.guiCheckboxBorderActive                 = sf::Color(  0,255,  0,128);
    dLink->settings.guiCheckboxBorderHover                  = sf::Color(  0,255,  0,255);
    dLink->settings.guiCheckboxBorderChecked                = sf::Color(255,255,255,255);


    dLink->settings.guiHorsliderButtonBackgroundInactive  = sf::Color( 40, 40, 40, 64);
    dLink->settings.guiHorsliderButtonBackgroundActive    = sf::Color( 40, 40, 40,128);
    dLink->settings.guiHorsliderButtonBackgroundHover     = sf::Color( 40, 40, 40,255);
    dLink->settings.guiHorsliderButtonBackgroundClicked   = sf::Color(  0,255,  0,255);
    dLink->settings.guiHorsliderButtonBorderInactive      = sf::Color( 80, 80, 80,128);
    dLink->settings.guiHorsliderButtonBorderActive        = sf::Color(  0,255,  0,128);
    dLink->settings.guiHorsliderButtonBorderHover         = sf::Color(  0,255,  0,255);
    dLink->settings.guiHorsliderButtonBorderClicked       = sf::Color(255,255,255,255);
    dLink->settings.guiHorsliderBarBackgroundInactive     = sf::Color( 40, 40, 40, 64);
    dLink->settings.guiHorsliderBarBackgroundActive       = sf::Color( 40, 40, 40,128);
    dLink->settings.guiHorsliderBarBorderInactive         = sf::Color( 80, 80, 80,128);
    dLink->settings.guiHorsliderBarBorderActive           = sf::Color(  0,255,  0,128);
    dLink->settings.guiHorsliderSliderBackgroundInactive  = sf::Color( 40, 40, 40, 64);
    dLink->settings.guiHorsliderSliderBackgroundActive    = sf::Color( 40, 40, 40,128);
    dLink->settings.guiHorsliderSliderBackgroundHover     = sf::Color( 40, 40, 40,255);
    dLink->settings.guiHorsliderSliderBackgroundMoving    = sf::Color(  0,255,  0,255);
    dLink->settings.guiHorsliderSliderBorderInactive      = sf::Color( 80, 80, 80,128);
    dLink->settings.guiHorsliderSliderBorderActive        = sf::Color(  0,255,  0,128);
    dLink->settings.guiHorsliderSliderBorderHover         = sf::Color(  0,255,  0,255);
    dLink->settings.guiHorsliderSliderBorderMoving        = sf::Color(255,255,255,255);

    dLink->settings.guiVertsliderButtonBackgroundInactive = sf::Color( 40, 40, 40, 64);
    dLink->settings.guiVertsliderButtonBackgroundActive   = sf::Color( 40, 40, 40,128);
    dLink->settings.guiVertsliderButtonBackgroundHover    = sf::Color( 40, 40, 40,255);
    dLink->settings.guiVertsliderButtonBorderInactive     = sf::Color( 80, 80, 80,128);
    dLink->settings.guiVertsliderButtonBorderActive       = sf::Color(  0,255,  0,128);
    dLink->settings.guiVertsliderButtonBorderHover        = sf::Color(  0,255,  0,255);
    dLink->settings.guiVertsliderBarBackgroundInactive    = sf::Color( 40, 40, 40, 64);
    dLink->settings.guiVertsliderBarBackgroundActive      = sf::Color( 40, 40, 40,128);
    dLink->settings.guiVertsliderBarBorderInactive        = sf::Color( 80, 80, 80,128);
    dLink->settings.guiVertsliderBarBorderActive          = sf::Color(  0,255,  0,128);
    dLink->settings.guiVertsliderSliderBackgroundInactive = sf::Color( 40, 40, 40, 64);
    dLink->settings.guiVertsliderSliderBackgroundActive   = sf::Color( 40, 40, 40,128);
    dLink->settings.guiVertsliderSliderBackgroundHover    = sf::Color( 40, 40, 40,255);
    dLink->settings.guiVertsliderSliderBackgroundMoving   = sf::Color(  0,255,  0,255);
    dLink->settings.guiVertsliderSliderBorderInactive     = sf::Color( 80, 80, 80,128);
    dLink->settings.guiVertsliderSliderBorderActive       = sf::Color(  0,255,  0,128);
    dLink->settings.guiVertsliderSliderBorderHover        = sf::Color(  0,255,  0,255);
    dLink->settings.guiVertsliderSliderBorderMoving       = sf::Color(255,255,255,255);


    dLink->settings.guiLabelTextInactive                  = sf::Color( 80, 80, 80,128);
    dLink->settings.guiLabelTextActive                    = sf::Color(  0,255,  0,255);
    dLink->settings.guiLabelTextHover                     = sf::Color(  0,255,  0,255);

    dLink->settings.guiTextboxBackgroundInactive          = sf::Color::Red;
    dLink->settings.guiTextboxBackgroundActive            = sf::Color::Red;
    dLink->settings.guiTextboxBackgroundHover             = sf::Color::Red;
    dLink->settings.guiTextboxBorderInactive              = sf::Color::Red;
    dLink->settings.guiTextboxBorderActive                = sf::Color::Red;
    dLink->settings.guiTextboxBorderHover                 = sf::Color::Red;

    dLink->settings.guiMenuTitleTextScale                 = 12;
    dLink->settings.guiButtonTextScale                    = 12;
    dLink->settings.guiHorsliderTextScale                 = 12;
    dLink->settings.guiVertsliderTextScale                = 12;
    dLink->settings.guiLabelTextScale                     = 12;
    dLink->settings.guiTextboxTextScale                   = 12;

    dLink->settings.guiMenuTitleFontID                    = "$_menuTitle";
    dLink->settings.guiButtonFontID                       = "$_menuTitle";
    dLink->settings.guiHorsliderFontID                    = "$_menuTitle";
    dLink->settings.guiVertsliderFontID                   = "$_menuTitle";
    dLink->settings.guiLabelFontID                        = "$_menuTitle";
    dLink->settings.guiTextboxFontID                      = "$_menuTitle";
}
void StockKeybinds()
{
    Action modeSwitch;
    modeSwitch.name = "modeSwitch";
    modeSwitch.ignitionDescriptor.type = sf::Event::KeyPressed;
    modeSwitch.ignitionDescriptor.key.code = sf::Keyboard::Tab;
    dLink->actions.push_back(modeSwitch);

    Action startTranslateForward;
    startTranslateForward.name = "startTranslateForward";
    startTranslateForward.ignitionDescriptor.type = sf::Event::KeyPressed;
    startTranslateForward.ignitionDescriptor.key.code = sf::Keyboard::W;
    dLink->actions.push_back(startTranslateForward);
    Action endTranslateForward;
    endTranslateForward.name = "endTranslateForward";
    endTranslateForward.ignitionDescriptor.type = sf::Event::KeyReleased;
    endTranslateForward.ignitionDescriptor.key.code = sf::Keyboard::W;
    dLink->actions.push_back(endTranslateForward);

    Action startTranslateBack;
    startTranslateBack.name = "startTranslateBack";
    startTranslateBack.ignitionDescriptor.type = sf::Event::KeyPressed;
    startTranslateBack.ignitionDescriptor.key.code = sf::Keyboard::S;
    dLink->actions.push_back(startTranslateBack);
    Action endTranslateBack;
    endTranslateBack.name = "endTranslateBack";
    endTranslateBack.ignitionDescriptor.type = sf::Event::KeyReleased;
    endTranslateBack.ignitionDescriptor.key.code = sf::Keyboard::S;
    dLink->actions.push_back(endTranslateBack);

    Action startTranslateLeft;
    startTranslateLeft.name = "startTranslateLeft";
    startTranslateLeft.ignitionDescriptor.type = sf::Event::KeyPressed;
    startTranslateLeft.ignitionDescriptor.key.code = sf::Keyboard::A;
    dLink->actions.push_back(startTranslateLeft);
    Action endTranslateLeft;
    endTranslateLeft.name = "endTranslateLeft";
    endTranslateLeft.ignitionDescriptor.type = sf::Event::KeyReleased;
    endTranslateLeft.ignitionDescriptor.key.code = sf::Keyboard::A;
    dLink->actions.push_back(endTranslateLeft);

    Action startTranslateRight;
    startTranslateRight.name = "startTranslateRight";
    startTranslateRight.ignitionDescriptor.type = sf::Event::KeyPressed;
    startTranslateRight.ignitionDescriptor.key.code = sf::Keyboard::D;
    dLink->actions.push_back(startTranslateRight);
    Action endTranslateRight;
    endTranslateRight.name = "endTranslateRight";
    endTranslateRight.ignitionDescriptor.type = sf::Event::KeyReleased;
    endTranslateRight.ignitionDescriptor.key.code = sf::Keyboard::D;
    dLink->actions.push_back(endTranslateRight);

    Action zoomOut;
    zoomOut.name = "zoomOut";
    zoomOut.ignitionDescriptor.type = sf::Event::MouseWheelMoved;
    zoomOut.ignitionDescriptor.mouseWheel.delta = -1;
    dLink->actions.push_back(zoomOut);
    Action zoomIn;
    zoomIn.name = "zoomIn";
    zoomIn.ignitionDescriptor.type = sf::Event::MouseWheelMoved;
    zoomIn.ignitionDescriptor.mouseWheel.delta = 1;
    dLink->actions.push_back(zoomIn);
}
