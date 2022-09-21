#include<iostream>
#include "airline.h"

using namespace std;

Queue::Queue() :
	max(0), pos(0), used(0) {
	pos = 0;
	used = 0;
	for (int i = 0; i < CAPACITY; i++) {
		queued[i] = 0;
	}
}

Queue::Queue(Queue& a) {
	this->used = a.used;
	this->max = a.max;
	this->pos = a.pos;

	for (int i = 0; i < size(); i++) {
		a.setPos(i);
		queued[i] = a.getElement();
	}
}

int Queue::getElement() {
	return queued[pos];
}

int Queue::size() const {
	return used;
}

void Queue::last() {
	if (empty() == false) {
		pos = used - 1;
	}
}

bool Queue::empty() {
	if (used == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Queue::erase() {
	for (int i = pos; i < used; i++) {
		queued[i] = queued[i + 1];
	}
	used = used - 1;
	pos = used - 1;
}

void Queue::insertAfter(int insert) {
	if (used + 1 > CAPACITY) {
		return;
	}
	if (used == 0) {
		queued[0] = insert;
		pos = queued[0];
	}
	else {
		for (int i = used; i > pos; i--) {
			queued[i] = queued[i - 1];
		}
		queued[pos + 1] = insert;
		pos++;
	}
	used++;
}

int Queue::maxLength(int max) {
	if (size() > max) {
		max = size();
	}
	return max;
}

int Queue::average(int total, int max) {
	int average = 0;
	average = total / max;
	return average;
}

void Queue::setPos(int num) {
	pos = num;
}

void Queue::first() {
	pos = 0;
}

void Queue::deque() {
	first();
	erase();
}

void Queue::enque(int v) {
	last();
	insertAfter(v);
}

int Queue::randFirstClass() {
	return rand() % 30 + 1;
}

int Queue::randBusinessClass() {
	return rand() % 15 + 1;
}

int Queue::randEconomyClass() {
	return rand() % 3 + 1;
}

int Queue::randFirstClassAgent() {
	return rand() % 5 + 20;
}

int Queue::randBusinessAgent() {
	return rand() % 6 + 12;
}

int Queue::randEconomyAgent() {
	return rand() % 5 + 10;
}

int main() {
	Queue firstClassLineQueue;
	Queue businessClassLineQueue;
	Queue economyClassLineQueue;

	cout
		<< "Enter the time (in minutes) for how long the simulation should be run: ";
	int timer;
	cin >> timer;
	while (timer < 1) {
		cout << "Invalid Input. Try Again" << endl;
		cin >> timer;
	}

	int firstClassAgent = 0;
	int businessAgent = 0;
	int economyAgent = 0;
	int firstClassMax = 0;
	int businessMax = 0;
	int economyMax = 0;
	int firstClassCustomers = 0;
	int businessCustomers = 0;
	int economyCustomers = 0;
	int firstClassTotal = 0;
	int businessTotal = 0;
	int economyTotal = 0;

	for (int i = 0; i < timer; ++i) {
		int firstClassLine = firstClassLineQueue.randFirstClass();
		int businessLine = businessClassLineQueue.randBusinessClass();
		int economyLine = economyClassLineQueue.randEconomyClass();
		//insert into queue
		if (firstClassLine == 1) {
			firstClassLineQueue.enque(1);
			firstClassTotal = firstClassTotal + 1;
			firstClassMax = firstClassLineQueue.maxLength(firstClassMax);
		}
		if (businessLine == 1) {
			businessClassLineQueue.enque(1);
			businessTotal = businessTotal + 1;
			businessMax = businessClassLineQueue.maxLength(businessMax);
		}
		if (economyLine == 1) {
			economyClassLineQueue.enque(1);
			economyTotal = economyTotal + 1;
			economyMax = economyClassLineQueue.maxLength(economyMax);
		}

		//First class agent sequences
		if (firstClassAgent != 0) {
			firstClassAgent = firstClassAgent - 1;
		}
		else if (firstClassLineQueue.empty() != true) {
			firstClassAgent = firstClassLineQueue.randFirstClassAgent();
			firstClassCustomers = firstClassAgent + firstClassCustomers;
			firstClassLineQueue.deque();
		}
		else {
			if (businessClassLineQueue.size() > 0 && businessAgent != 0) {
				firstClassAgent = businessClassLineQueue.randBusinessAgent();
				businessCustomers = firstClassAgent + businessCustomers;
				businessClassLineQueue.deque();
			}
			else if (economyClassLineQueue.size() > 0 && economyAgent != 0) {
				firstClassAgent = economyClassLineQueue.randEconomyAgent();
				economyCustomers = firstClassAgent + economyCustomers;
				economyClassLineQueue.deque();
			}
			else {
				firstClassAgent = 0;
			}
		}
		//business class agent sequences
		if (businessAgent != 0) {
			businessAgent = businessAgent - 1;
		}
		else if (businessClassLineQueue.empty() != true) {
			businessAgent = businessClassLineQueue.randBusinessAgent();
			businessCustomers = businessAgent + businessCustomers;
			businessClassLineQueue.deque();
		}
		else {
			if (firstClassLineQueue.size() > 0 && firstClassAgent != 0) {
				businessAgent = firstClassLineQueue.randFirstClassAgent();
				firstClassCustomers = businessAgent + firstClassCustomers;
				firstClassLineQueue.deque();
			}
			else if (economyClassLineQueue.size() > 0 && economyAgent != 0) {
				businessAgent = economyClassLineQueue.randEconomyAgent();
				economyCustomers = businessAgent + economyCustomers;
				economyClassLineQueue.deque();
			}
			else {
				businessAgent = 0;
			}
		}
		//economy class agent sequences
		if (economyAgent != 0) {
			economyAgent = economyAgent - 1;
		}
		else if (economyClassLineQueue.empty() != true) {
			economyAgent = economyClassLineQueue.randEconomyAgent();
			economyCustomers = economyAgent + economyCustomers;
			economyClassLineQueue.deque();
		}
		else {
			if (firstClassLineQueue.size() > 0 && firstClassAgent != 0) {
				economyAgent = firstClassLineQueue.randFirstClassAgent();
				firstClassCustomers = economyAgent + firstClassCustomers;
				firstClassLineQueue.deque();
			}
			else if (businessClassLineQueue.size() > 0
				&& businessAgent != 0) {
				economyAgent = businessClassLineQueue.randBusinessAgent();
				businessCustomers = economyAgent + businessCustomers;
				businessClassLineQueue.deque();
			}
			else {
				economyAgent = 0;
			}
		}
		if (i % 10 == 0) {
			cout << "There are " << firstClassLineQueue.size()
				<< " people in the First Class line." << endl;
			cout << "There are " << businessClassLineQueue.size()
				<< " people in the Business Class line." << endl;
			cout << "There are " << economyClassLineQueue.size()
				<< " people in the Economy Class line." << endl;
			if (firstClassAgent == 0) {
				cout << "The First Class agent is not busy." << endl;
			}
			else {
				cout << "The First Class agent is busy." << endl;
			}
			if (businessAgent == 0) {
				cout << "The Business Class agent is not busy." << endl;
			}
			else {
				cout << "The Business Class agent is busy." << endl;
			}
			if (economyAgent == 0) {
				cout << "The Economy Class agent is not busy." << endl;
			}
			else {
				cout << "The Economy Class agent is busy." << endl;
			}
		}
	}

	cout << "The average line length for the First Class line was "
		<< firstClassLineQueue.average(firstClassTotal, firstClassMax)
		<< "." << endl;
	cout << "The average line length for the Business Class line was "
		<< businessClassLineQueue.average(businessTotal, businessMax) << "."
		<< endl;
	cout << "The average line length for the Economy Class line was "
		<< economyClassLineQueue.average(economyTotal, economyMax) << "."
		<< endl;

	cout << "The max line length for the First Class line was "
		<< firstClassLineQueue.maxLength(firstClassMax) << "." << endl;
	cout << "The max line length for the Business Class line was "
		<< businessClassLineQueue.maxLength(businessMax) << "." << endl;
	cout << "The max line length for the Economy Class line was "
		<< economyClassLineQueue.maxLength(economyMax) << "." << endl;

	cout << "The average time spent in line for the First Class customer was "
		<< firstClassTotal
		/ firstClassLineQueue.average(firstClassTotal,
			firstClassMax) << " minutes." << endl;
	cout
		<< "The average time spent in line for the Business Class customer was "
		<< businessTotal
		/ businessClassLineQueue.average(businessTotal, businessMax)
		<< " minutes." << endl;
	cout << "The average time spent in line for the Economy Class customer was "
		<< economyTotal
		/ economyClassLineQueue.average(economyTotal, economyMax)
		<< " minutes." << endl;

	cout << "The average time an agent spent on the First Class customer was "
		<< firstClassCustomers / firstClassTotal << " minutes." << endl;
	cout
		<< "The average time an agent spent on the Business Class customer was "
		<< businessCustomers / businessTotal << " minutes." << endl;
	cout << "The average time an agent spent on the Economy Class customer was "
		<< economyCustomers / economyTotal << " minutes." << endl;

	return 0;
}