#pragma once
#include <string>
#include <fstream>

const int SIZE_OF_STRINGS = 64;

class File {
public:
	struct Date {
		unsigned short int day;
		unsigned short int month;
		unsigned short int year;
		Date(int year = 1970, int month = 1, int day = 1) :day(day), month(month), year(year) {};
	};
private:
	char folderName[SIZE_OF_STRINGS];
	char name[SIZE_OF_STRINGS];
	char specification[SIZE_OF_STRINGS];
	Date date;
	unsigned long int size;
public:
	File() {
		date = Date(); size = 0;
		for (int i = 0; i < SIZE_OF_STRINGS; ++i) {
			(this->name)[i] = ' ';
			(this->folderName)[i] = ' ';
			(this->specification)[i] = ' ';
		}
	}
	File(char folderName[SIZE_OF_STRINGS], char name[SIZE_OF_STRINGS], char specification[SIZE_OF_STRINGS], Date date = Date(), size_t size = 0) : date(date), size(size) {
		for (int i = 0; i < SIZE_OF_STRINGS; ++i) {
			(this->name)[i] = name[i];
			(this->folderName)[i] = folderName[i];
			(this->specification)[i] = specification[i];
		}
	}

	bool operator>(const File& file);
	bool operator<(const File& file);
	bool operator==(const File& file);

	friend std::istream& operator>>(std::istream& stream, File& file);
	friend std::ostream& operator<<(std::ostream& stream, File& file);

	void setDate(Date date) { this->date = date; }
	void setSize(unsigned long int size) { this->size = size; }

	std::string getFolderName() { return folderName; }
	std::string getName() { return name; }
	std::string getSpecification() { return specification; }
	Date getDate() { return date; }
	unsigned long int getSize() { return size; }
};

bool File::operator>(const File& file) {
	bool result;
	if (folderName > file.folderName ||
		folderName == file.folderName && name > file.name ||
		folderName == file.folderName && name == file.name && specification > file.specification)
	{
		result = true;
	}
	else {
		result = false;
	}
	return result;


}
bool File::operator<(const File& file) {
	bool result;
	if (folderName < file.folderName ||
		folderName == file.folderName && name < file.name ||
		folderName == file.folderName && name == file.name && specification < file.specification)
	{
		result = true;
	}
	else {
		result = false;
	}
	return result;
}
bool File::operator==(const File& file) {
	bool result;
	if (folderName == file.folderName && name == file.name && specification == file.specification) {
		result = true;
	}
	else {
		result = false;
	}
	return result;
}

std::istream& operator>>(std::istream& stream, File& file) {

	stream >> file.folderName;
	stream >> file.name;
	stream >> file.specification;
	stream >> file.date.day;
	stream >> file.date.month;
	stream >> file.date.year;
	stream >> file.size;

	return stream;
}

std::ostream& operator<<(std::ostream& stream, File& file) {

	stream << file.folderName << "\n";
	stream << file.name << '\n';
	stream << file.specification << '\n';
	stream << file.date.day << ' ';
	stream << file.date.month << ' ';
	stream << file.date.year << '\n';
	stream << file.size << '\n';

	return stream;
}