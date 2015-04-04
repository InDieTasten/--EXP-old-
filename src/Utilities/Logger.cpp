#include <Utilities/Logger.hpp>
#include <sstream>
#include <SFML\System.hpp>


namespace EXP
{
	sf::Mutex loggermtx;
}
void EXP::log(std::string msg)
{
	time_t rawtime;
	struct tm * timeinfo;

	char T[14];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(T, 14, "%j|%H:%M:%S", timeinfo);

	loggermtx.lock();
	std::cout << "&f" << T << msg << std::endl;
	loggermtx.unlock();
}
//void LOG::file(std::string msg)
//{
//	time_t rawtime;
//	struct tm * timeinfo;
//
//	char T[14];
//
//	time(&rawtime);
//	timeinfo = localtime(&rawtime);
//
//	strftime(T, 14, "%j|%H:%M:%S", timeinfo);
//
//	std::stringstream ss;
//	ss << "&f" << T << msg;
//	logger.log(ss.str());
//	if (true) // SAFEMODE
//		std::cout << "&f" << T << msg << std::endl;
//}
//void LOG::safe(std::string msg)
//{
//	if (!true) //SAFEMODE
//		return;
//	time_t rawtime;
//	struct tm * timeinfo;
//
//	char T[14];
//
//	time(&rawtime);
//	timeinfo = localtime(&rawtime);
//
//	strftime(T, 14, "%j|%H:%M:%S", timeinfo);
//
//	std::stringstream ss;
//	ss << "&f" << T << msg;
//	logger.log(ss.str());
//}
