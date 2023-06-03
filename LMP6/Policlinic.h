#pragma once
#include <vector>
#include "Person.h"
#include <memory>
#include <functional>
#include <algorithm>

using info_t = std::unique_ptr<Person>;
using ps_ptr = std::vector<info_t>;

class Policlinic
{
private:
	ps_ptr List;
	std::string name;
public:
	Policlinic(std::string name = "");
	std::string get_name();
	ps_ptr::iterator get_begin();
	ps_ptr::iterator get_end();
	void set_name(std::string);
	void add_by_order(info_t person);
	void add_to_begin(info_t person);
	void add_to_end(info_t person);
	void move_to_end(const Person& person);
	void sort();
	void remove(Person person);
	void erase_if(std::function<bool(const info_t&)> lambda);
	friend std::ostream& operator << (std::ostream& output, Policlinic& object);
};
