#ifndef _Conversion_hpp_
#define _Conversion_hpp_

namespace utils {
	template<class T>
	std::string tostring(T i)
	{
		std::stringstream ss;
		std::string s;
		ss << i;
		s = ss.str();

		return s;
	}
}

#endif // !_Conversion_hpp_