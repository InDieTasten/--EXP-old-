
#include <Utilities/FileLogger.hpp>
/* FileLogger:
	Logs everything to the Filesystem*/

FileLogger::FileLogger()
{
	try
	{
		if (_mkdir("logs") == 0)
		{

		}

		time_t rawtime;
		struct tm * timeinfo;

		char T[14];

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(T, 14, "%j_%H-%M-%S", timeinfo);

		std::string t = "logs/";
		t += T;
		t += "_untitled.ulog";

		logfile.open(t.c_str(), std::ios::out | std::ios::trunc);


	}
	catch (...)
	{
		log("Log could not be created");
	}


}


FileLogger::~FileLogger()
{

	logfile.close();
}



void FileLogger::log(std::string temp)
{

	try
	{
		GMutex.lock();
		logfile << temp << "\n";
		GMutex.unlock();
	}
	catch (...)
	{

	}




}

