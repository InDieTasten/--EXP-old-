//includes
#include <Utilities\VERSION.hpp>
#include <Utilities\Logger.hpp>
#include <SFML\Graphics.hpp>
#include <Input\EventManager.hpp>

extern sf::Mutex loggermtx;
extern void EXP::log(std::string);
extern void EXP::init();

//TESTZONE START
#include <Data\Mesh.hpp>
//TESTZONE END


extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


namespace EXP {
	EventManager* eventManager = nullptr;
}

void gameQuit(sf::Event::KeyEvent _event)
{
	if (_event.code == sf::Keyboard::Escape)
	{
		EXP::eventManager->terminate();
	}
}

int main(int argc, char *argv[])
{
	EXP::init();
	EXP::log("[Info]Game is launching in version: " + VERSION::version);
	sf::RenderWindow Window(sf::VideoMode(1280, 720, 32), VERSION::name + " " + VERSION::version, sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
	sf::View view = Window.getDefaultView();
	view.setCenter(0.0f, 0.0f);
	Window.setView(view);

	EXP::eventManager = new EventManager(&Window);
	EXP::eventManager->addKeyRelease(&gameQuit);

	//TESTZONE START
	Mesh* test1 = new Mesh();

	test1->addVertex(sf::Vertex(sf::Vector2f(-20, 20)));
	test1->addVertex(sf::Vertex(sf::Vector2f(20, 20)));
	test1->addVertex(sf::Vertex(sf::Vector2f(20, -20)));
	test1->addVertex(sf::Vertex(sf::Vector2f(-10, -10)));
	test1->addVertex(sf::Vertex(sf::Vector2f(5, 5)));
	
	Mesh* test2 = new Mesh();

	test2->addVertex(sf::Vertex(sf::Vector2f(-10, 10)));
	test2->addVertex(sf::Vertex(sf::Vector2f(30, 10)));
	test2->addVertex(sf::Vertex(sf::Vector2f(30, -30)));
	test2->addVertex(sf::Vertex(sf::Vector2f(0, -20)));
	test2->addVertex(sf::Vertex(sf::Vector2f(15, 0)));

	std::list<sf::Vector2f> coll = test1->overlap(sf::Transform(), test2, sf::Transform().translate(5, 0));
	Window.clear();
	for (auto point : coll)
	{
		EXP::log("[Debug]Render circle: " + utils::tostring(point.x) + utils::tostring(point.y));
		sf::CircleShape shape(4.0/8.0);
		shape.setOutlineColor(sf::Color::Red);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineThickness(1.0/8.0);
		shape.setPosition(point);
		shape.setOrigin(4.0 / 8.0, 4.0 / 8.0);
		sf::Transform pos;
		pos.scale(8.0, 8.0);
		Window.draw(shape, pos);
	}

	
	sf::Transformable x;
	x.setScale(8.0,8.0);
	
	test1->draw(&Window, x, sf::Color(0, 255, 0, 32));
	x.move(5*8, 0);
	test2->draw(&Window, x, sf::Color(0, 0, 255, 32));
	Window.display();

	delete test1;
	test1 = nullptr;
	delete test2;
	test2 = nullptr;
	//TESTZONE END

	EXP::eventManager->listen();

	delete EXP::eventManager;
	EXP::eventManager = nullptr;

	Window.close();

	EXP::log("[Info]Game quit!");
	return EXIT_SUCCESS;
}
