#ifndef _TestCode_hpp_
#define _TestCode_hpp_

#include <string>
#include <exception>
#include <iostream>
#include <SFML\System.hpp>

#include <Utilities\Conversion.hpp>
#include <Data\Vector.hpp>
namespace tests {
	void tester(void(*_testFunc)(void)) {
		try {
			std::cout << "Running test: ";
			sf::sleep(sf::milliseconds(30));
			_testFunc();
			std::cout << "PASSED" << std::endl;
		}
		catch (std::string ex)
		{
			std::cout << "FAILED @" << std::endl << ex << std::endl;
		}
	}

	//Utilities
	//Utilities/Conversion
	//Utilities/Conversion/tostring
	void Utilities_Conversion_tostring_integerConversion()
	{
		if (utils::tostring(1) != std::string("1"))
			throw std::string("Utilities_Conversion_tostring_integerConversion: unexpected return value");
	}
	void Utilities_Conversion_tostring_stringConversion()
	{
		if (utils::tostring(std::string("Hallo Welt!")) != std::string("Hallo Welt!"))
			throw std::string("Utilities_Conversion_tostring_stringConversion: unexpected return value");
	}
	void Utilities_Conversion_tostring_floatConversion()
	{
		if (utils::tostring((float)1.6f) != std::string("1.6"))
			throw std::string("Utilities_Conversion_tostring_floatConversion: unexpected return value");
	}
	void Utilities_Conversion_tostring_doubleConversion()
	{
		if (utils::tostring((double)1.6f) != std::string("1.6"))
			throw std::string("Utilities_Conversion_tostring_doubleConversion: unexpected return value");
	}
	//Data
	//Data/Vector
	void Data_Vector_Constructor_Default()
	{
		Vector x;
		if (x.getX() != 0.0f)
			throw std::string("Data_Vector_Constructor_Default: wrong X member initialization");
		if (x.getY() != 0.0f)
			throw std::string("Data_Vector_Constructor_Deafult: wrong Y member initialization");
		if (x.getR() != 0.0f)
			throw std::string("Data_Vector_Constructor_Deafult: wrong R member initialization");
	}
	void Data_Vector_Constructor_1()
	{
		Vector x(1.0f, 2.0f, 4.0f);
		if (x.getX() != 1.0f)
			throw std::string("Data_Vector_Constructor_1: wrong X member initialization");
		if (x.getY() != 2.0f)
			throw std::string("Data_Vector_Constructor_1: wrong Y member initialization");
		if (x.getR() != 4.0f)
			throw std::string("Data_Vector_Constructor_1: wrong R member initialization");
	}
	//WORK
}

#include <Utilities\Logger.hpp>

namespace EXP {
	void testCode()
	{
		try {
			tests::tester(&tests::Utilities_Conversion_tostring_integerConversion);
			tests::tester(&tests::Utilities_Conversion_tostring_stringConversion);
			tests::tester(&tests::Utilities_Conversion_tostring_floatConversion);
			tests::tester(&tests::Utilities_Conversion_tostring_doubleConversion);
			tests::tester(&tests::Data_Vector_Constructor_Default);
			tests::tester(&tests::Data_Vector_Constructor_1);
		}
		catch (std::exception ex) {
			std::cout << "Strange exception in test code throwing following what(): " << ex.what() << std::endl;
		}
		catch (std::string ex) {
			std::cout << "Strange exception in test code throwing following std::string: " << ex << std::endl;
		}
		catch (...) {
			std::cout << "Something really strange happened in test code" << std::endl;
		}
	}
}

#endif // !_TestCode_hpp_