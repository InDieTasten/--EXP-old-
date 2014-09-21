#ifndef _DataBank_hpp_
#define _DataBank_hpp_

#include <SFML\Graphics.hpp>
#include <list>
#include "Texture.hpp"
#include "Font.hpp"
#include "Sound.hpp"
#include "Track.hpp"
#include "SolarSystem.hpp"
#include "Camera.hpp"
#include "Script.hpp"
#include <direct.h>
#include <fstream>
#include <sstream>
#include "Logger.hpp"
#include "KeyBind.hpp"
#include "Settings.hpp"
#include "Level.hpp"
#include "Debug.hpp"

class DataBank
{
    //MEMBERS
private:
    std::list<KeyBind> keybindings;
    std::list<Script> scripts;
    std::list<Texture> textures;
    std::list<Font> fonts;
    std::list<Sound> sounds;
    std::list<Track> tracks;
public:
    sf::RenderWindow *renderWindow;
    Level level;
    bool guiMode;
    bool runGraphics;
    bool runPhysics;
    bool runModules;

    Settings settings;
    Debug debug;

    std::list<std::list<std::string> > softEvents;
    std::list<std::list<std::string> > softTasks;

    //CONSTRUCTORS
    DataBank();

    //DESTRUCTORS

    //METHODS

    //Texture Management
    void TextureRegister(std::string _id, std::string _path);
    void TextureErase(std::string _id);
    void TextureLoad(std::string _id);
    void TextureUnload(std::string _id);
    sf::Texture* TextureGet(std::string _id);

    //Font Management
    void FontRegister(std::string _id, std::string _path);
    void FontErase(std::string _id);
    void FontLoad(std::string _id);
    void FontUnload(std::string _id);
    sf::Font* FontGet(std::string _id);

    //Sound Management
    void SoundRegister(std::string _id, std::string _path);
    void SoundErase(std::string _id);
    void SoundLoad(std::string _id);
    void SoundUnload(std::string _id);
    sf::SoundBuffer* SoundGet(std::string _id);

    //Track Management
    void TrackRegister(std::string _id, std::string _path);
    void TrackErase(std::string _id);
    void TrackLoad(std::string _id);
    void TrackUnload(std::string _id);
    sf::SoundBuffer* TrackGet(std::string _id);

    //Views
    sf::View gameView;
    sf::View guiView;

    //Files
    void saveDataBank(std::string _path);
    void loadDataBank(std::string _path);

    //Events
    void pushEvent(std::list<std::string> _args);
    std::list<std::string> pullEvent();
    void pushTask(std::list<std::string> _args);
    std::list<std::string> pullTask();
    void handleSoftEvent(std::list<std::string> _args);
    void handleTask     (std::list<std::string> _args);
};

#endif
