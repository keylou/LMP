#pragma once
#include "Person.h"

class Patient : public Person
{
private:
	int age;
	int num_policy;
public:
	Patient(std::string fio = "", bool sex = true, int age = 0, int num_policy = 0);

	int get_age();
	int get_policy();
	void set_age(int);
	void set_policy(int);
	std::string toString() override;
};
