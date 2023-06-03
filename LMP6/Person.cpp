#include "Person.h"

Person::Person(std::string fio, bool sex) : fio(fio), sex(sex) {};

Person::~Person() {}

std::string Person::get_fio()
{
	return fio;
}

bool Person::get_sex()
{
	return sex;
}

void Person::set_fio(std::string val)
{
	fio = val;
}

void Person::set_sex(bool val)
{
	sex = val;
}

int Person::comp(const Person& object)
{
	int result = 1;
	if (sex < object.sex)
		result = -1;
	else if (fio == object.fio)
		result = 0;
	return result;
}

std::string Person::toString()
{
	std::string output = "ФИО: " + fio + "; пол: ";
	if (sex)
		output += "мужчина";
	else
		output += "женщина";
	return output;
}