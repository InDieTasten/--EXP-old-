#ifndef _Video_hpp_
#define _Video_hpp_

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