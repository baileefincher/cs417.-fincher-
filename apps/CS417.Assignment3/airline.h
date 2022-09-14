#pragma once

#include <cstdlib>

class Queue {
private:
	static const int CAPACITY = 100;
	int max;
	int pos;
	int used;
	int queued[CAPACITY];
public:
	Queue();

	Queue(Queue& other);

	void last();

	int getElement();

	int size() const;

	bool empty();

	void erase();

	void first();

	void deque();

	void enque(int v);

	void insertAfter(int);

	int randFirstClass();

	int randBusinessClass();

	int randEconomyClass();

	int randFirstClassAgent();

	int randBusinessAgent();

	int randEconomyAgent();

	int maxLength(int max);

	int average(int total, int max);

	void setPos(int pos);
};