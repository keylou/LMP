#include "Patient.h"

Patient::Patient(std::string fio, bool sex, int age, int num_policy) : Person(fio, sex), age(age), num_policy(num_policy) {};

int Patient::get_age()
{
	return age;
}

int Patient::get_policy()
{
	return num_policy;
}

void Patient::set_age(int val)
{
	age = val;
}

void Patient::set_policy(int val)
{
	num_policy = val;
}

std::string Patient::toString()
{
	return "Пациент: " + Person::toString() + ", возраст: " + std::to_string(age) + ", номер мед. полиса: " + std::to_string(num_policy);
}