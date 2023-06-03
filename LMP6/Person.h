#pragma once
#include <iostream>
#include <string>

class Person
{
private:
	std::string fio;
	bool sex; // true - мужчина, false - женщина
public:
	Person(std::string fio = "", bool = true);
	virtual ~Person();
	std::string get_fio();
	bool get_sex();
	void set_fio(std::string);
	void set_sex(bool);
	int comp(const Person&);
	virtual std::string toString();
};