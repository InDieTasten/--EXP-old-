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
// Thread Throttleling
float EvtThread =  60.0; //Cycles per second
float ModThread =  40.0; //Cycles per second
float PhyThread = 100.0; //Cycles per second
float VidThread =  60.0; //Cycles per second
sf::Mutex GMutex;

void StockRegister(DataBank* datalink);

using namespace std;


int main ( int argc, char *argv[] )
{
    //Test-Zone
    std::cout << "\nTESTZONE\n\n";

    Loader loader;
    std::list<std::string> content;
    content = loader.getFolderContent("./content/stock/scripts");
    cout << "Size: " << content.size() << endl;
    for(std::list<std::string>::iterator it = content.begin(); it != content.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "\n\nTESTZONE\n";
    //Test-Zone

    try
    {
        int DEBUG_LEVEL = 99;
        Logger init;
        init.init(&DEBUG_LEVEL, "init        ");
        init.log(20, "Logger enabled");
        ////////////////////
        // 1. DataBank    //
        //                //
        // 2. GUIManager  //
        //                //
        // 3. Processing  //
        ////////////////////

        ///// 1. DataBank
        init.log(20, "Create Memory Mangager Instance...");
        DataBank dBank(&DEBUG_LEVEL);
        init.log(20, "Registrate Prime Camera...");
        dBank.CameraRegister("mainCam", Vector(0.0f,0.0f), 0.0f);
        init.log(20, "Set active camera to Primary Cam...");
        dBank.CameraSetActive("mainCam");

        //App Instance
        init.log(20, "Generate RenderDevice(Window)...");
        sf::RenderWindow App(sf::VideoMode(1280, 720, 32), "[[UntitledGame]]", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
        init.log(20, "Re-Apply view...");
        sf::View View(App.getDefaultView());
        init.log(20, "Launch RenderLink...");
        dBank.renderWindow = &App;
        init.log(20, "Launch ViewLink...");
        dBank.standardView = &View;


        StockRegister(&dBank);

        // 2. GUIManager
        init.log(20, "Create GUI Instance...");
        GUIManager gManager;
        gManager.SetDataLink(&dBank);

        // 3. Processing
        //Graphics Engine
        init.log(20, "Create Graphics Thread...");
        GraphicsEngine graphicsThread(&dBank, &gManager, &DEBUG_LEVEL);
        init.log(20, "Relocate Render Thread...");
        App.setActive(false);
        //Physics Engine
        init.log(20, "Create Physics Thread...");
        PhysicsEngine physicsThread(&dBank, &DEBUG_LEVEL);
        //Modding Module
        init.log(20, "Create Plugin Handler...");
        ModModule mModule;
        mModule.SetDataLink(&dBank, &gManager, &DEBUG_LEVEL);
        //Event Manager
        init.log(20, "Create Event Manager...");
        EventManager EventMan;
        EventMan.SetDataLink(&dBank, &gManager, &graphicsThread, &physicsThread, &mModule, &DEBUG_LEVEL);

        //Starting Engines
        init.log(20, "Launch Plugins...");
        sf::Thread plTHREAD(&ModModule::Run, &mModule);
        plTHREAD.launch();
        init.log(20, "Launch Graphics...");
        sf::Thread grTHREAD(&GraphicsEngine::Run, &graphicsThread);
        grTHREAD.launch();
        init.log(20, "Launch Physics...");
        sf::Thread phTHREAD(&PhysicsEngine::Run, &physicsThread);
        phTHREAD.launch();
        init.log(20, "Initialization finished :)");
        init.log(20, "Switch from Init to Main(-Event)-Logger");

        Logger logger;
        logger.init(&DEBUG_LEVEL, "Main        ");
        sf::Clock timer;
        sf::Clock limit;
        timer.restart();
        limit.restart();
        while(App.isOpen())
        {
            GMutex.unlock();
            if(limit.getElapsedTime().asSeconds() < 1.0/EvtThread)
            {
                sf::sleep(sf::seconds(1.0/EvtThread - limit.getElapsedTime().asSeconds()));
            }
            limit.restart();
            GMutex.lock();
            if (timer.getElapsedTime().asSeconds() > 1.0f)
            {
                logger.log(11,"Thread running");
                timer.restart();
            }
            sf::Event Event;
            while(App.pollEvent(Event))
            {
                EventMan.processEvent(&Event);
                //DEBUG
                if(Event.type == sf::Event::KeyPressed)
                {
                    ostringstream x;
                    x << "Key Code -> " << Event.key.code << endl;
                    logger.log(1, x.str());
                }
            }
            while(dBank.softEvents.size() != 0)
            {
                EventMan.processSoftEvent(dBank.pullEvent());
            }
        }
        GMutex.unlock();
    }
    catch (std::exception &e)
    {
        printf(*e.what() + "\n");
        _getch();
    }
    catch (...)
    {
        std::printf("Fatal Error: Unexpected non std::exception thrown!");
    }
    printf("\n=|=|=|=|=|=|=|=|=|=|=|=|=|=\n\nThe game closed. If you see errors above, pls contact the developers");
    //getchar();
    return EXIT_SUCCESS;
}

void StockRegister(DataBank* dBank)
{
    //stock resources
    dBank->FontRegister   ("$_menuTitle"          , "content/stock/font/lucon.ttf");

    dBank->TextureRegister("$_closeButtonNormal"  , "content/stock/texture/gui/window/titleBar/closeButton/normal.png");
    dBank->TextureRegister("$_closeButtonHover"   ,  "content/stock/texture/gui/window/titleBar/closeButton/hover.png");
    dBank->TextureRegister("$_closeButtonPushed"  , "content/stock/texture/gui/window/titleBar/closeButton/pushed.png");
    dBank->TextureRegister("$_dockMain"           , "content/stock/texture/gui/dock/main.png");
    dBank->TextureRegister("$_dockOptions"        , "content/stock/texture/gui/dock/options.png");
    dBank->TextureRegister("$_missing"            , "content/stock/texture/missing.png");


    dBank->FontLoad   ("$_menuTitle");

    dBank->TextureLoad("$_closeButtonNormal");
    dBank->TextureLoad("$_closeButtonHover");
    dBank->TextureLoad("$_closeButtonPushed");
    dBank->TextureLoad("$_dockMain");
    dBank->TextureLoad("$_dockOptions");
    dBank->TextureLoad("$_missing");
}
