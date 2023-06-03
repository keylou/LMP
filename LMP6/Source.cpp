#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Patient.h"
#include "Policlinic.h"
#include "Medic.h"

void init(Policlinic& policlinic, std::fstream& file)
{
	char t;
	while (file >> t)
	{
		std::string fio, is_sex, ln, fn, mn;
		bool sex;
		file >> ln >> fn >> mn;
		fio = ln + ' ' + fn + ' ' + mn;
		file >> is_sex;
		if (is_sex == "м")
		{
			sex = true;
		}
		else
		{
			sex = false;
		}
		if (t == 'П')
		{
			int age, num_policy;
			file >> age >> num_policy;
			Patient ptn = Patient(fio, sex, age, num_policy);
			policlinic.add_by_order(std::move(std::make_unique<Patient>(ptn)));
		}
		else
		{
			std::string cat, qual;
			int exp;
			file >> qual >> exp >> cat;
			Medic mdc = Medic(fio, sex, exp, qual, Medic::str_to_type(cat));
			policlinic.add_by_order(std::move(std::make_unique<Medic>(mdc)));
		}
	}
	file.close();
}

//void task(Policlinic& policlinic, int age)
//{
//	std::string str;
//	ps_ptr::iterator patientmale = policlinic.get_begin();
//	while (patientmale != policlinic.get_end())
//	{
//		Patient* t = dynamic_cast<Patient*>(patientmale->get());
//		Person* g = dynamic_cast<Person*>(t);
//		if (g && g->get_sex())
//		{
//			policlinic.remove(g);
//		}
//	}
//}

void task(Policlinic& policlinic, int age)
{
	auto check = [](const info_t& Person)->bool {
		Patient* t = dynamic_cast<Patient*>(Person.get());
		bool result = false;
		if (t && t->get_sex())
			result = true;
		return result;
	};
	policlinic.erase_if(check);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::fstream file("input.txt");
	Policlinic policlinic("Electronic");
	init(policlinic, file);
	std::cout << "Введите нужный возраст" << std::endl;
	int age;
	std::cin >> age;
	std::cout << policlinic << std::endl;
	task(policlinic, age);
	std::cout << "Отредактированный список пациентов: " << policlinic << std::endl;
}