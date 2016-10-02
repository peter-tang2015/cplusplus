#pragma once
#include <string>

class Student 
{
public:
	Student(void);
	~Student(void);
	
	enum Sex {
		MALE,
		FEMALE,
		OTHER
	};

	enum Majority {
		PHYSICS,
		MATH,
		COMPTUER_SCIENCE,
		ECONOMOICS,
	};

	void TakeCourse();

private:
	std::string m_Name;
	unsigned char m_Age;
	Sex m_Sex;
	Majority m_Majority;

};

