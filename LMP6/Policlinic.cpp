#include "Policlinic.h"

Policlinic::Policlinic(std::string name) : name(name) {}

std::string Policlinic::get_name()
{
	return name;
}

ps_ptr::iterator Policlinic::get_begin()
{
	return List.begin();
}

ps_ptr::iterator Policlinic::get_end()
{
	return List.end();
}

void Policlinic::set_name(std::string val)
{
	name = val;
}

void Policlinic::add_by_order(info_t person)
{
	auto i = List.begin();
	while (i != List.end() && (*i)->comp(*person) == -1)
	{
		i++;
	}
	List.insert(i, std::move(person));
}

void Policlinic::add_to_begin(info_t person)
{
	List.insert(List.begin(), std::move(person));
}

void Policlinic::add_to_end(info_t person)
{
	List.push_back(std::move(person));
}

void Policlinic::move_to_end(const Person& person)
{
	for (auto i = List.begin(); i != List.end();)
	{
		if ((*i)->comp(person) == 0)
		{
			i = List.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void Policlinic::sort()
{
	std::sort(List.begin(), List.end(), [](const info_t& Ps1, const info_t& Ps2) {return Ps1->comp(*Ps2) == -1; });
}

void Policlinic::remove(Person person)
{
	for (auto i = List.begin(); i != List.end();)
		if ((*i)->comp(person) == 0)
			i = List.erase(i);
		else ++i;
}

void Policlinic::erase_if(std::function<bool(const info_t&)> lambda)
{
	auto i = std::remove_if(List.begin(), List.end(), lambda);
	List.erase(i, List.end());
}

std::ostream& operator<<(std::ostream& output, Policlinic& object)
{
	for (const info_t& Ps : object.List)
	{
		output << Ps->toString() << "\n";
	}
	return output;
}