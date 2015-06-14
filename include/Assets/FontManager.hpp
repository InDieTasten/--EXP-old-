#ifndef _FontManager_hpp_
#define _FontManager_hpp_

#include <map>
#include <Assets\Font.hpp>
#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

extern void EXP::log(std::string);

class FontManager
{
private:
	std::map<std::string, Font*> fonts;

public:
	FontManager();
	~FontManager();

	void addFont(std::string _id, std::string _path);
	void removeFont(std::string _id);
	Font* getFont(std::string _id);
};

#endif // !_FontManager_hpp_
