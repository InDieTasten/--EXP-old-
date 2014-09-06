#ifndef _Settings_hpp_
#define _Settings_hpp_

struct Settings
{
    sf::Color guiMenuBorderInactive;
    sf::Color guiMenuBorderActive;
    sf::Color guiMenuBackgroundInactive;
    sf::Color guiMenuBackgroundActive;
    sf::Color guiMenuTitleBackgroundInactive;
    sf::Color guiMenuTitleBackgroundActive;
    sf::Color guiMenuTitleTextInactive;
    sf::Color guiMenuTitleTextActive;
    sf::Color guiButtonBackgroundInactive;
    sf::Color guiButtonBackgroundActive;
    sf::Color guiButtonBackgroundHover;
    sf::Color guiButtonBorderInactive;
    sf::Color guiButtonBorderActive;
    sf::Color guiButtonBorderHover;
    sf::Color guiButtonTextColorInactive;
    sf::Color guiButtonTextColorActive;
    sf::Color guiButtonTextColorHover;

    std::string guiTitleFont;

    int dockWidth;
};

#endif
