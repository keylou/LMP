#include <fstream>
#include <iostream>
#include "File.h"
#include "HashMap.h"
#include <Windows.h>

void fill(HashMap<std::string, File>& hash, std::ifstream& file) {
	File f;
	while (!file.eof()) {
		file >> f;
		std::pair<std::string, File> p(f.getName(), f);
		hash.add(p);
	}

}

int main() {
	SetConsoleOutputCP(1251);
	HashMap<std::string, File> hash(5);
	std::ifstream file("input.txt");
	fill(hash, file);

	int nextMoove = -1;

	while (nextMoove != 4) {
		std::cout << "\n1. Вывести все имена файлов\n2. Вывести информацию о файле по имени\n3. Удалить файл по имени\n4. Выход\n";
		std::cin >> nextMoove;
		if (nextMoove == 1) {
			hash.print();
		}
		else if (nextMoove == 2) {
			std::cout << "Имя файла: ";
			std::string name;
			std::cin >> name;
			if (hash.find(name)) {
				std::cout << hash[name];
			}
			else {
				std::cout << "Файл не найден";
			}
		}
		else if (nextMoove == 3) {
			std::cout << "Имя файла для удаления: ";
			std::string name;
			std::cin >> name;
			hash.remove(name);
		}
	}
}