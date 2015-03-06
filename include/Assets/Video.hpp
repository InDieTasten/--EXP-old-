#ifndef _Video_hpp_
#define _Video_hpp_

#include <Assets\Asset.hpp>

using namespace std;

class Video : public Asset
{
private:
	int* data;

public:
	int* getVideo();
	void load();
	void unload();
};

#endif // !_Video_hpp_