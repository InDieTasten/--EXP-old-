#ifndef _Menu_hpp_
#define _Menu_hpp_

#include <list>
#include <SFML\Graphics.hpp>

using namespace std;
extern void ug::log(std::string);

class GUIManager;

class Menu
{
private:
	GUIManager* parent;

	//list<Button*> buttons;
	//list<Label*> labels;
	//list<Textbox*> textboxes;
	//list<HorSlider*> horsliders;
	//list<VertSlider*> vertsliders;
	//list<CheckBox*> checkboxes;
	//list<Canvas*> canvases;
	//list<ProgressBar*> progressbars;
	//list<PictureBox*> pictureboxes;
	//list<VideoPlayer*> videoplayers;

	sf::RenderTarget* thingy;
public:
	Menu(GUIManager* _parent);
	~Menu();

	void render(sf::RenderWindow* _window);
	void show();
	void hide();
	//void addButton(string, Button);
	//void removeButton(string*);
	//void removeButton(Button*);
	//Button* getButton(string*);

};

#endif // !_Menu_hpp_