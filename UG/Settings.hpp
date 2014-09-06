#ifndef _Settings_hpp_
#define _Settings_hpp_

struct Settings
{
    sf::Color   guiMenuBorderInactive;
    sf::Color   guiMenuBorderActive;
    sf::Color   guiMenuBackgroundInactive;
    sf::Color   guiMenuBackgroundActive;
    sf::Color   guiMenuTitleBackgroundInactive;
    sf::Color   guiMenuTitleBackgroundActive;
    sf::Color   guiMenuTitleTextInactive;
    sf::Color   guiMenuTitleTextActive;
    int         guiMenuTitleHeight;
    int         guiMenuTitleTextScale;
    std::string guiTitleFont;

    sf::Color   guiButtonBackgroundInactive;
    sf::Color   guiButtonBackgroundActive;
    sf::Color   guiButtonBackgroundHover;
    sf::Color   guiButtonBorderInactive;
    sf::Color   guiButtonBorderActive;
    sf::Color   guiButtonBorderHover;
    sf::Color   guiButtonTextInactive;
    sf::Color   guiButtonTextActive;
    sf::Color   guiButtonTextHover;
    int         guiButtonTextScale;
    std::string guiButtonFontID;

    sf::Color   guiLabelTextInactive;
    sf::Color   guiLabelTextActive;
    sf::Color   guiLabelTextHover;
    int         guiLabelTextScale;
    std::string guiLabelFontID;



    int dockWidth;
};

#endif
