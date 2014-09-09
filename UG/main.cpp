//includes
#include <iostream>
#include "DataBank.hpp"
#include "Vector.hpp"
#include "Actor.hpp"
#include "GUIManager.hpp"
#include "GraphicsEngine.hpp"
#include "PhysicsEngine.hpp"
#include "ModModule.hpp"
#include "EventManager.hpp"
#include <conio.h>
#include "Logger.hpp"
#include "Loader.hpp"
#include <list>
#include <time.h>
#include "util.hpp"
#include <SFML\System.hpp>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


// Thread Throttleling
float mLimit =  100.0; //Cycles per second
float gLimit =  60.0; //Cycles per second
float pLimit =  500.0; //Cycles per second
float mainLimit =  100.0; //Cycles per second

// Global accessors
std::list< std::list<std::string> > eventBuffer;
std::list< std::list<std::string> > taskBuffer;
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

using namespace std;

int main ( int argc, char *argv[] )
{
    log("Main      ", "Logger enabled");
    ////////////////////
    // 1. DataBank    //
    //                //
    // 2. GUIManager  //
    //                //
    // 3. Processing  //
    ////////////////////

    ///// 1. DataBank
    log("Main      ", "Create Memory Mangager Instance...");
    DataBank dBank;
    dLink = &dBank;

    //App Instance
    log("Main      ", "Generate RenderDevice(Window)...");
    sf::RenderWindow App(sf::VideoMode(1280, 720, 32), "[[UntitledGame]]", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    log("Main      ", "Re-Apply view...");
    dLink->gameView = App.getDefaultView();
    dLink->guiView = App.getDefaultView();
    log("Main      ", "Launch RenderLink...");
    dLink->renderWindow = &App;

    StockRegister();
    StockSettings();

    // 2. GUIManager
    log("Main      ", "Create GUI Instance...");
    GUIManager gManager;
    guiLink = &gManager;

    // 3. Processing
    //Graphics Engine
    log("Main      ", "Create Graphics Thread...");
    GraphicsEngine graphicsThread;
    gLink = &graphicsThread;
    log("Main      ", "Relocate Render Thread...");
    App.setActive(false);

    //Physics Engine
    log("Main      ", "Create Physics Thread...");
    sf::sleep(sf::seconds(0.05));
    PhysicsEngine physicsThread;
    pLink = &physicsThread;

    //Modding Module
    log("Main      ", "Create Plugin Handler...");
    sf::sleep(sf::seconds(0.05));
    ModModule mModule;
    mLink = &mModule;

    //Event Manager
    log("Main      ", "Create Event Manager...");
    sf::sleep(sf::seconds(0.05));
    EventManager EventMan;

    StockKeybinds();

    ////Create threads
    sf::Thread plTHREAD(&ModModule::Run, &mModule);
    sf::Thread grTHREAD(&GraphicsEngine::Run, &graphicsThread);
    sf::Thread phTHREAD(&PhysicsEngine::Run, &physicsThread);

    mThread = &plTHREAD;
    gThread = &grTHREAD;
    pThread = &phTHREAD;

    mThread->launch();
    sf::sleep(sf::seconds(0.3));
    gThread->launch();
    sf::sleep(sf::seconds(0.1));
    pThread->launch();


    sf::Music music;
    music.openFromFile("content/stock/music/background.wav");
    music.setVolume(20);
    music.setLoop(true);
    music.play();


    sf::Clock limit;
    limit.restart();
    while(App.isOpen())
    {
        GMutex.unlock();
        if(limit.getElapsedTime().asSeconds() < 1.0/mainLimit)
        {
            sf::sleep(sf::seconds(1.0/mainLimit - limit.getElapsedTime().asSeconds()));
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

    printf("\n=|=|=|=|=|=|=|=|=|=|=|=|=|=\n\nThe game closed. If you see errors above, pls contact the developers");
    //getchar();
    return EXIT_SUCCESS;
}

void StockRegister()
{
    //stock resources
    dLink->FontRegister   ("$_menuTitle"          , "content/stock/font/lucon.ttf");

    dLink->TextureRegister("$_closeButtonNormal"  , "content/stock/texture/gui/window/titleBar/closeButton/normal.png");
    dLink->TextureRegister("$_closeButtonHover"   , "content/stock/texture/gui/window/titleBar/closeButton/hover.png" );
    dLink->TextureRegister("$_closeButtonPushed"  , "content/stock/texture/gui/window/titleBar/closeButton/pushed.png");
    dLink->TextureRegister("$_dockMain"           , "content/stock/texture/gui/dock/main.png"                         );
    dLink->TextureRegister("$_dockOptions"        , "content/stock/texture/gui/dock/options.png"                      );
    dLink->TextureRegister("$_missing"            , "content/stock/texture/missing.png"                               );

}
void StockSettings()
{

    dLink->settings.dockWidth = 67;


    dLink->settings.guiDockBackground          = sf::Color::Black;
    dLink->settings.guiDockBackgroundHover     = sf::Color::Green;
    dLink->settings.guiDockBorder              = sf::Color::Green;
    dLink->settings.guiDockBorderHover         = sf::Color::White;
    dLink->settings.guiDockItemBackground      = sf::Color::Red;
    dLink->settings.guiDockItemBackgroundHover = sf::Color::Red;
    dLink->settings.guiDockItemBorder          = sf::Color::Red;
    dLink->settings.guiDockItemBorderHover     = sf::Color::Red;


    dLink->settings.guiMenuTitleTextScale = 12;
    dLink->settings.guiButtonTextScale = 12;
    dLink->settings.guiHorsliderTextScale = 12;
    dLink->settings.guiLabelTextScale = 12;
    dLink->settings.guiTextboxTextScale = 12;

    dLink->settings.guiMenuTitleFont   = "$_menuTitle";
    dLink->settings.guiButtonFontID    = "$_menuTitle";
    dLink->settings.guiHorsliderFontID = "$_menuTitle";
    dLink->settings.guiLabelFontID     = "$_menuTitle";
    dLink->settings.guiTextboxFontID   = "$_menuTitle";
}
void StockKeybinds()
{

}
