//includes
#include <Utilities\Logger.hpp>
#include <SFML\Graphics.hpp>
#include <Input\EventManager.hpp>
#include <Processing\GameEngine.hpp>

extern sf::Mutex loggermtx;
extern void EXP::log(std::string);
extern void EXP::init();


//TESTZONE START

#include <Input\EventHandler.hpp>
Delegate<double> del;
EventHandler<float> handler;
class me {
public:
	me()
	{
		handler += Delegate<float>(this, &me::nadu);
		handler(nullptr, 13.37f);
	}
private:
	void nadu(EventPublisher* sender, float value)
	{
		std::cout << "Received: " << value << std::endl;
	}
};
me call;

#include <..\EXP-ExpandedExploration\TestCode.hpp>
extern void EXP::testCode();
//TESTZONE END


extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <luabind\luabind.hpp>

int gameStart(int argc, char *argv[])
{
	EXP::init();


	GameEngine* engine = new GameEngine();
	engine->launch();

	delete engine;
	engine = nullptr;



	EXP::log("[Info]Game quit! Securing all threads have terminated");
	sf::sleep(sf::seconds(1));
	return EXIT_SUCCESS;
}
void test();
int main(int argc, char *argv[])
{
	//Running test code
	try {
		EXP::testCode();
	}
	catch (std::exception ex) {
		EXP::log("[FATAL]Test code failed: " + std::string(ex.what()));
		return EXIT_FAILURE;
	}
	//Running game code
	gameStart(argc, argv);
	return EXIT_SUCCESS;
}
