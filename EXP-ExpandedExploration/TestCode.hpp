#ifndef _TestCode_hpp_
#define _TestCode_hpp_

#include <string>
#include <exception>
#include <iostream>
#include <SFML\System.hpp>

#include <Utilities\Conversion.hpp>
#include <Data\Vector.hpp>
#include <Data\Taggable.hpp>

namespace tests {
	int failed = 0;
	int succeed = 0;
	void tester(void(*_testFunc)(void)) {
		try {

			sf::sleep(sf::milliseconds(30));
			_testFunc();
			std::cout << "Running test : PASSED" << std::endl;
			succeed++;
			return;
		}
		catch (std::string ex)
		{
			std::cout << "Running test : FAILED @" << std::endl << ex << std::endl;
			failed++;
			return;
		}
	}

	//SFML
	//SFML/Sprite
	void SFML_Sprite_Destruction1()
	{
		sf::Sprite x;
	}
	void SFML_Sprite_Destruction2()
	{
		sf::Sprite* x = new sf::Sprite();
		delete x;
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
	void Data_Vector_setX()
	{
		Vector test;
		test.setX(1.0f);
		if (test.getX() != 1.0f)
			throw std::string("Data_Vector_setX: wrong value set");
	}
	void Data_Vector_setY()
	{
		Vector test;
		test.setY(1.0f);
		if (test.getY() != 1.0f)
			throw std::string("Data_Vector_setY: wrong value set");
	}
	void Data_Vector_setR()
	{
		Vector test;
		test.setR(1.0f);
		if (test.getR() != 1.0f)
			throw std::string("Data_Vector_setR: wrong value set");
	}
	void Data_Vector_operatorAdd()
	{
		Vector first(1.0f, 1.0f, 1.0f);
		Vector second(2.0f, 2.0f, 2.0f);

		Vector result = first + second;
		if (result.getX() != 3.0f)
			throw std::string("Data_Vector_operatorAdd: wrong member X result");
		if (result.getY() != 3.0f)
			throw std::string("Data_Vector_operatorAdd: wrong member Y result");
		if (result.getR() != 3.0f)
			throw std::string("Data_Vector_operatorAdd: wrong member R result");
	}
	void Data_Vector_operatorSubtract()
	{
		Vector first(5.0f, 6.0f, 7.0f);
		Vector second(2.0f, 3.0f, 4.0f);

		Vector result = first - second;
		if (result.getX() != 3.0f)
			throw std::string("Data_Vector_operatorSubtract: wrong member X result");
		if (result.getY() != 3.0f)
			throw std::string("Data_Vector_operatorSubtract: wrong member Y result");
		if (result.getR() != 3.0f)
			throw std::string("Data_Vector_operatorSubtract: wrong member R result");
	}
	void Data_Vector_operatorMultiply()
	{
		Vector first(5.0f, 6.0f, 7.0f);
		Vector second(2.0f, 3.0f, 4.0f);

		Vector result = first * second;
		if (result.getX() != 10.0f)
			throw std::string("Data_Vector_operatorMultiply: wrong member X result");
		if (result.getY() != 18.0f)
			throw std::string("Data_Vector_operatorMultiply: wrong member Y result");
		if (result.getR() != 28.0f)
			throw std::string("Data_Vector_operatorMultiply: wrong member R result");
	}
	void Data_Vector_operatorDevide()
	{
		Vector first(9.0f, 12.0f, 15.0f);
		Vector second(3.0f, 3.0f, 2.0f);

		Vector result = first / second;
		if (result.getX() != 3.0f)
			throw std::string("Data_Vector_operatorDevide: wrong member X result");
		if (result.getY() != 4.0f)
			throw std::string("Data_Vector_operatorDevide: wrong member Y result");
		if (result.getR() != 7.5f)
			throw std::string("Data_Vector_operatorDevide: wrong member R result");
	}
	void Data_Vector_operatorAddEqual()
	{
		Vector first(1.0f, 1.0f, 1.0f);
		Vector second(2.0f, 2.0f, 2.0f);

		first += second;
		if (first.getX() != 3.0f)
			throw std::string("Data_Vector_operatorAddEqual: wrong member X result");
		if (first.getY() != 3.0f)
			throw std::string("Data_Vector_operatorAddEqual: wrong member Y result");
		if (first.getR() != 3.0f)
			throw std::string("Data_Vector_operatorAddEqual: wrong member R result");
	}
	void Data_Vector_operatorSubtractEqual()
	{
		Vector first(5.0f, 6.0f, 7.0f);
		Vector second(2.0f, 3.0f, 4.0f);

		first -= second;
		if (first.getX() != 3.0f)
			throw std::string("Data_Vector_operatorSubtractEqual: wrong member X result");
		if (first.getY() != 3.0f)
			throw std::string("Data_Vector_operatorSubtractEqual: wrong member Y result");
		if (first.getR() != 3.0f)
			throw std::string("Data_Vector_operatorSubtractEqual: wrong member R result");
	}
	void Data_Vector_operatorMultiplyEqual()
	{
		Vector first(5.0f, 6.0f, 7.0f);
		Vector second(2.0f, 3.0f, 4.0f);

		first *= second;
		if (first.getX() != 10.0f)
			throw std::string("Data_Vector_operatorMultiplyEqual: wrong member X result");
		if (first.getY() != 18.0f)
			throw std::string("Data_Vector_operatorMultiplyEqual: wrong member Y result");
		if (first.getR() != 28.0f)
			throw std::string("Data_Vector_operatorMultiplyEqual: wrong member R result");
	}
	void Data_Vector_operatorDevideEqual()
	{
		Vector first(9.0f, 12.0f, 15.0f);
		Vector second(3.0f, 3.0f, 2.0f);

		first /= second;
		if (first.getX() != 3.0f)
			throw std::string("Data_Vector_operatorDevideEqual: wrong member X result");
		if (first.getY() != 4.0f)
			throw std::string("Data_Vector_operatorDevideEqual: wrong member Y result");
		if (first.getR() != 7.5f)
			throw std::string("Data_Vector_operatorDevideEqual: wrong member R result");
	}
	void Data_Vector_operatorAdd_float()
	{
		Vector first(1.0f, 1.0f, 1.0f);

		Vector result = first + 2.0f;
		if (result.getX() != 3.0f)
			throw std::string("Data_Vector_operatorAdd_float: wrong member X result");
		if (result.getY() != 3.0f)
			throw std::string("Data_Vector_operatorAdd_float: wrong member Y result");
		if (result.getR() != 3.0f)
			throw std::string("Data_Vector_operatorAdd_float: wrong member R result");
	}
	void Data_Vector_operatorSubtract_float()
	{
		Vector first(7.0f, 6.0f, 5.0f);

		Vector result = first - 2.0f;
		if (result.getX() != 5.0f)
			throw std::string("Data_Vector_operatorSubtract_float: wrong member X result");
		if (result.getY() != 4.0f)
			throw std::string("Data_Vector_operatorSubtract_float: wrong member Y result");
		if (result.getR() != 3.0f)
			throw std::string("Data_Vector_operatorSubtract_float: wrong member R result");
	}
	void Data_Vector_operatorMultiply_float()
	{
		Vector first(7.0f, 6.0f, 5.0f);

		Vector result = first * 2.0f;
		if (result.getX() != 14.0f)
			throw std::string("Data_Vector_operatorMultiply_float: wrong member X result");
		if (result.getY() != 12.0f)
			throw std::string("Data_Vector_operatorMultiply_float: wrong member Y result");
		if (result.getR() != 10.0f)
			throw std::string("Data_Vector_operatorMultiply_float: wrong member R result");
	}
	void Data_Vector_operatorDevide_float()
	{
		Vector first(7.0f, 6.0f, 5.0f);

		Vector result = first / 2.0f;
		if (result.getX() != 3.5f)
			throw std::string("Data_Vector_operatorDevide_float: wrong member X result");
		if (result.getY() != 3.0f)
			throw std::string("Data_Vector_operatorDevide_float: wrong member Y result");
		if (result.getR() != 2.5f)
			throw std::string("Data_Vector_operatorDevide_float: wrong member R result");
	}
	void Data_Vector_operatorAddEqual_float()
	{
		Vector first(1.0f, 1.0f, 1.0f);

		first += 2.0f;
		if (first.getX() != 3.0f)
			throw std::string("Data_Vector_operatorAddEqual_float: wrong member X result");
		if (first.getY() != 3.0f)
			throw std::string("Data_Vector_operatorAddEqual_float: wrong member Y result");
		if (first.getR() != 3.0f)
			throw std::string("Data_Vector_operatorAddEqual_float: wrong member R result");
	}
	void Data_Vector_operatorSubtractEqual_float()
	{
		Vector first(7.0f, 6.0f, 5.0f);

		first -= 2.0f;
		if (first.getX() != 5.0f)
			throw std::string("Data_Vector_operatorSubtractEqual_float: wrong member X result");
		if (first.getY() != 4.0f)
			throw std::string("Data_Vector_operatorSubtractEqual_float: wrong member Y result");
		if (first.getR() != 3.0f)
			throw std::string("Data_Vector_operatorSubtractEqual_float: wrong member R result");
	}
	void Data_Vector_operatorMultiplyEqual_float()
	{
		Vector first(7.0f, 6.0f, 5.0f);

		first *= 2.0f;
		if (first.getX() != 14.0f)
			throw std::string("Data_Vector_operatorMultiplyEqual_float: wrong member X result");
		if (first.getY() != 12.0f)
			throw std::string("Data_Vector_operatorMultiplyEqual_float: wrong member Y result");
		if (first.getR() != 10.0f)
			throw std::string("Data_Vector_operatorMultiplyEqual_float: wrong member R result");
	}
	void Data_Vector_operatorDevideEqual_float()
	{
		Vector first(7.0f, 6.0f, 5.0f);

		first /= 2.0f;
		if (first.getX() != 3.5f)
			throw std::string("Data_Vector_operatorDevideEqual_float: wrong member X result");
		if (first.getY() != 3.0f)
			throw std::string("Data_Vector_operatorDevideEqual_float: wrong member Y result");
		if (first.getR() != 2.5f)
			throw std::string("Data_Vector_operatorDevideEqual_float: wrong member R result");
	}
	//Data/Taggable
	void Data_Taggable_Constructor_Default()
	{
		Taggable test;
		if (test.getTag("TestTag") != 0.0f)
			throw std::string("Data_Taggable_Constructor_Default: Ghost tag allocated");
	}
	void Data_Taggable_setTag()
	{
		Taggable test;
		test.setTag("TestTag", 1.5f);
		if (test.getTag("TestTag") != 1.5f)
			throw std::string("Data_Taggable_setTag: Bad Tag value");
	}
	void Data_Taggable_getTags()
	{
		Taggable test;
		test.setTag("TestTag", 1.0f);
		std::map<std::string, float> testTags = test.getTags();
		if (testTags["TestTag"] != 1.0f)
			throw std::string("Data_Taggable_getTags: Bad Tag value");
	}
	void Data_Taggable_setTags()
	{
		Taggable test;
		test.setTag("TestTag", 1.0f);
		std::map<std::string, float> testTags = test.getTags();
		testTags["TestTag2"] = 7.5f;
		test.setTags(testTags);
		if (test.getTag("TestTag2") != 7.5f)
			throw std::string("Data_Taggable_getTags: Bad Tag value for new Tag");
		if (test.getTag("TestTag") != 1.0f)
			throw std::string("Data_Taggable_getTags: Bad Tag value for old Tag");
	}
	void Data_Taggable_moveTag()
	{
		Taggable test;
		test.setTag("TestTag", 1.0f);
		test.moveTag("TestTag", 3.0f);
		if (test.getTag("TestTag") != 4.0f)
			throw std::string("Data_Taggable_moveTag: Bad Tag value for moved Tag");
	}
	//Input
	//Input/EventManager
	void Input_EventManager_Constructor_1()
	{
		try {
			sf::RenderWindow testWindow;
			EventManager test(testWindow);
		}
		catch (...)
		{
			throw std::string("Input_EventManager_Constructor_1: Could not construct");
		}
	}
}

#include <Utilities\Logger.hpp>

namespace EXP {
	void testCode()
	{
		EXP::log(" [Info]==Init Logger==");
		int failed = 0;
		try {
			tests::tester(&tests::SFML_Sprite_Destruction1);
			tests::tester(&tests::SFML_Sprite_Destruction2);

			tests::tester(&tests::Utilities_Conversion_tostring_integerConversion);
			tests::tester(&tests::Utilities_Conversion_tostring_stringConversion);
			tests::tester(&tests::Utilities_Conversion_tostring_floatConversion);
			tests::tester(&tests::Utilities_Conversion_tostring_doubleConversion);

			tests::tester(&tests::Data_Vector_Constructor_Default);
			tests::tester(&tests::Data_Vector_Constructor_1);
			tests::tester(&tests::Data_Vector_setX);
			tests::tester(&tests::Data_Vector_setY);
			tests::tester(&tests::Data_Vector_setR);
			tests::tester(&tests::Data_Vector_operatorAdd);
			tests::tester(&tests::Data_Vector_operatorSubtract);
			tests::tester(&tests::Data_Vector_operatorMultiply);
			tests::tester(&tests::Data_Vector_operatorDevide);
			tests::tester(&tests::Data_Vector_operatorAddEqual);
			tests::tester(&tests::Data_Vector_operatorSubtractEqual);
			tests::tester(&tests::Data_Vector_operatorMultiplyEqual);
			tests::tester(&tests::Data_Vector_operatorDevideEqual);
			tests::tester(&tests::Data_Vector_operatorAdd_float);
			tests::tester(&tests::Data_Vector_operatorSubtract_float);
			tests::tester(&tests::Data_Vector_operatorMultiply_float);
			tests::tester(&tests::Data_Vector_operatorDevide_float);
			tests::tester(&tests::Data_Vector_operatorAddEqual_float);
			tests::tester(&tests::Data_Vector_operatorSubtractEqual_float);
			tests::tester(&tests::Data_Vector_operatorMultiplyEqual_float);
			tests::tester(&tests::Data_Vector_operatorDevideEqual_float);

			tests::tester(&tests::Data_Taggable_Constructor_Default);
			tests::tester(&tests::Data_Taggable_setTag);
			tests::tester(&tests::Data_Taggable_getTags);
			tests::tester(&tests::Data_Taggable_setTags);
			tests::tester(&tests::Data_Taggable_moveTag);

			tests::tester(&tests::Input_EventManager_Constructor_1);

			std::cout << std::endl << std::endl << tests::succeed << "/" << tests::failed + tests::succeed << " Tests succeeded! Finishing up..." << std::endl;
			sf::sleep(sf::seconds(2));
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
