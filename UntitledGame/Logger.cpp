#include "Logger.hpp"
//CONSTRUCTORS
//DESTRUCTORS
//METHODS
void Logger::init(int* _level, std::string _source)
{
	Level = _level;
	while(_source.length() < 12)
	{
		_source = _source+" ";
	}
	Source = _source;
}
void Logger::log(int detail,std::string msg)
{
	if(detail <= *Level)
	{
		time_t Zeitstempel;
		tm *nun;
		Zeitstempel = time(0);
		nun = localtime(&Zeitstempel);
		localtime_s(nun, &Zeitstempel);
		char buffer [80];
		strftime (buffer,80,"%j|%X",nun);
		std::ostringstream sstream;
		if(detail < 10)
			sstream << buffer <<" [0"<<detail<<" "<<Source<<"] "<< msg <<std::endl;
		else
			sstream << buffer <<" ["<<detail<<" "<<Source<<"] "<< msg <<std::endl;
		std::string result= sstream.str();

		//writing to console
		std::cout << result;
		//writing to file
		//missing
	}
}