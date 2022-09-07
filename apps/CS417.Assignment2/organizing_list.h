#pragma once

#include <algorithm>
#include <iostream>
#include <list>

template<typename T>
class SelfOrganizingList {
private:
	std::list<T> lst;

public:

	SelfOrganizingList() {
	}

	SelfOrganizingList(const SelfOrganizingList& other) :
		lst(other.lst) {
	}

	~SelfOrganizingList() {
	}

	SelfOrganizingList& operator=(const SelfOrganizingList& other) {
		lst = other.lst;
		return *this;
	}

	void moveToFront(T t) {
		auto itr = std::find(begin(), end(), t);
		if (itr != end()) {
			lst.erase(itr);
			push_front(t);
			return;
		}
	}

	void push_front(T t) {
		lst.push_front(t);
	}

	void push_back(T t) {
		lst.push_back(t);
	}

	typename std::list<T>::iterator begin() {
		return lst.begin();
	}

	typename std::list<T>::iterator end() {
		return lst.end();
	}

	int size() {
		return lst.size();
	}

	void print() {
		for (auto itr = begin(); itr != end(); itr++) {
			std::cout << *itr << std::endl;
		}
	}
};