#ifndef _Video_hpp_
#define _Video_hpp_

#include <Assets\Asset.hpp>

#include <list>

using namespace std;
extern void ug::log(std::string);

class Video : public Asset
{
private:
	int* data;

public:
	Video(string* _id, string _path);
	~Video();

	void load();
	void unload();
};

#endif // !_Video_hpp_