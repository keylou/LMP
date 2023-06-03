#pragma once
#include "Person.h"

enum Type
{
	first,
	second,
	highest
};

class Medic : public Person
{
private:
	Type cat;
	int exp;
	std::string qual;
public:
	Medic(std::string fio = "", bool sex = true, int exp = 0, std::string qual = "", Type cat = first);
	Type get_cat();
	int get_exp();
	std::string get_qual();
	void set_cat(std::string);
	void set_exp(int);
	void set_qual(std::string);
	std::string Get_type_string();
	static Type str_to_type(std::string);
	std::string toString() override;
};
