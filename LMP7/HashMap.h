#pragma once
#include <vector>
#include <functional>
#include <fstream>
#include <iostream>

const float maxPercent = 0.8f;

template <class Key, class T>
class HashMap {
private:
	int size;
	int elemCount;
	std::vector<bool> isFilled;
	std::vector<std::pair<Key, T>> vector;
	void resize(int new_size);
	int hash(std::string k) { // чтобы хешкод был меньше размера моего вектора
		int sum = 0;
		for (size_t i = 0; i < k.length(); ++i) {
			sum += k[i];
		}
		return sum % size;
	};
public:
	void print();


	HashMap(int size = 10) : elemCount(0), size(size) {
		vector.resize(size);
		isFilled.resize(size);
		for (int i = 0; i < size; ++i) {
			isFilled[i] = false;
		}

	}

	void foreach(std::function<void(T&)> f) {
		for (int i = 0; i < size; ++i) {
			if (isFilled[i]) {
				f(vector[i].second);
			}
		}
	}

	T& operator[](Key k);
	bool add(std::pair<Key, T>& elem);
	bool remove(Key k);
	bool find(Key k);



};


template<class Key, class T>
inline void HashMap<Key, T>::resize(int new_size)
{
	int old_size = size;
	size = new_size;

	std::vector<std::pair<Key, T>> tempv = vector;
	std::vector<bool> tempf = isFilled;

	isFilled.resize(size);
	for (int i = 0; i < size; ++i) {
		isFilled[i] = false;
	}
	vector.resize(size);

	elemCount = 0;
	for (int i = 0; i < old_size; ++i) {
		if (tempf[i]) {
			add(tempv[i]);
		}
	}
}

template<class Key, class T>
inline void HashMap<Key, T>::print()
{
	for (int i = 0; i < size; ++i) {
		std::cout << i << ": ";
		if (isFilled[i]) {
			std::cout << vector[i].first << '(' << hash(vector[i].first) << ')';
		}
		std::cout << '\n';
	}
}

template<class Key, class T>
inline T& HashMap<Key, T>::operator[](Key k)
{

	bool isFind = false;
	int ind = hash(k);
	T* result = nullptr;

	int curr = ind;

	while (isFilled[curr] && !isFind) {
		if (vector[curr].first == k) {
			isFind = true;
		}
		else {
			curr = (curr + 1) % size;
		}
	}
	if (isFind) {
		T& res = vector[curr].second;
		result = &res;
	}


	return *result;
}


template<class Key, class T>
inline bool HashMap<Key, T>::add(std::pair<Key, T>& elem)
{
	bool isAdd = true;
	int curr = hash(elem.first);


	while (isFilled[curr] && isAdd) { // если €чейка заполнена и флаг isadd подн€т, двигаюсь по кольцу и провер€ю на совпадение. 
		if (elem.first == vector[curr].first) {
			isAdd = false;
		}
		else {
			curr = (curr + 1) % size;
		}
	}


	if (isAdd) { // если прошел по вектору и не нашел совпадени€, довабл€ю элемент
		vector[curr] = elem;
		isFilled[curr] = true;
		++elemCount;

		if (elemCount > size * maxPercent) { // рехеширование
			resize(size * 2);
		}
	}
	return isAdd;
}


template<class Key, class T>
inline bool HashMap<Key, T>::remove(Key k)
{
	bool isRemoved = false;
	int ind = hash(k);
	int curr = ind;

	auto len = [=](int x, int y) {return (x - y + size) % size; };

	while (isFilled[curr] && !isRemoved) {
		if (vector[curr].first == k) {
			isRemoved = true;
		}
		else {
			curr = (curr + 1) % size;
		}
	}

	if (isRemoved) {
		--elemCount;
		isFilled[curr] = false;
		int find = (curr + 1) % size;
		while (isFilled[find]) {
			int hashInd = hash(vector[find].first);
			if (len(curr, find) >=hashInd)
			{
				isFilled[curr] = true;
				isFilled[find] = false;

				std::swap(vector[curr], vector[find]);
				curr = find;
			}

			find = (find + 1) % size;
		}
	}


	return isRemoved;
}

template<class Key, class T>
inline bool HashMap<Key, T>::find(Key k)
{
	bool isFind = false;
	int ind = hash(k);
	int curr = (ind);

	while (isFilled[curr] && !isFind) {
		if (vector[curr].first == k) {
			isFind = true;
		}
		curr = (curr + 1) % size;
	}
	return isFind;
}

