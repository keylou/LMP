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
		std::cout << "\n1. ������� ��� ����� ������\n2. ������� ���������� � ����� �� �����\n3. ������� ���� �� �����\n4. �����\n";
		std::cin >> nextMoove;
		if (nextMoove == 1) {
			hash.print();
		}
		else if (nextMoove == 2) {
			std::cout << "��� �����: ";
			std::string name;
			std::cin >> name;
			if (hash.find(name)) {
				std::cout << hash[name];
			}
			else {
				std::cout << "���� �� ������";
			}
		}
		else if (nextMoove == 3) {
			std::cout << "��� ����� ��� ��������: ";
			std::string name;
			std::cin >> name;
			hash.remove(name);
		}
	}
}