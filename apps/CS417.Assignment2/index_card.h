#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>

class Card {
private:
	int index;
	std::string keyword;

public:
	Card(int index, std::string keyword);

	Card(const Card& other);

	~Card();

	int getIndex() const;

	std::string getKeyword() const;

	Card& operator=(const Card& other);

	bool operator==(const Card& other) const;

	bool operator<(const Card& other) const;

	bool operator>(const Card& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Card& dt) {
		os << dt.index << " -> " << dt.keyword;
		return os;
	}
};

class IndexCards {
private:
	std::list<Card> cardsByIndex;
	std::list<Card> cardsByKeyword;

	void insertByIndex(Card card);
	void insertByKeyword(Card card);
	void print(std::list<Card> theList);
	std::vector<Card> toVector(std::list<Card> theList);
	void removeCard(std::list<Card>& cards, Card card);

public:
	IndexCards();

	IndexCards(const IndexCards& other);

	~IndexCards();

	IndexCards& operator=(const IndexCards& other);

	void insert(Card card);

	void printByIndex();

	void printByKeyword();

	std::vector<Card> getByIndex();

	std::vector<Card> getByKeyword();

	void removeCard(Card card);

};

Card::Card(int index, std::string keyword) :
	index(index), keyword(keyword) {
}

Card::Card(const Card& other) :
	index(other.index), keyword(other.keyword) {
}

Card::~Card() {
}

int Card::getIndex() const {
	return index;
}

std::string Card::getKeyword() const {
	return keyword;
}

Card& Card::operator=(const Card& other) {
	index = other.index;
	keyword = other.keyword;
	return *this;
}

bool Card::operator==(const Card& other) const {
	return index == other.index && keyword == other.keyword;
}

bool Card::operator<(const Card& other) const {
	return index < other.index;
}

bool Card::operator>(const Card& other) const {
	return index > other.index;
}

IndexCards::IndexCards() {
}

IndexCards::IndexCards(const IndexCards& other) :
	cardsByIndex(other.cardsByIndex), cardsByKeyword(other.cardsByKeyword) {
}

IndexCards::~IndexCards() {
}

IndexCards& IndexCards::operator=(const IndexCards& other) {
	cardsByIndex = other.cardsByIndex;
	cardsByKeyword = other.cardsByKeyword;
	return *this;
}

void IndexCards::insertByIndex(Card card) {
	for (auto itr = cardsByIndex.begin(); itr != cardsByIndex.end(); itr++) {
		if (card < *itr) {
			cardsByIndex.insert(itr, card);
			return;
		}
	}

	cardsByIndex.push_back(card);
}

void IndexCards::insertByKeyword(Card card) {
	for (auto itr = cardsByKeyword.begin(); itr != cardsByKeyword.end();
		itr++) {
		if (card.getKeyword() < (*itr).getKeyword()) {
			cardsByKeyword.insert(itr, card);
			return;
		}
	}

	cardsByKeyword.push_back(card);
}

void IndexCards::insert(Card card) {
	insertByIndex(card);
	insertByKeyword(card);
}

void IndexCards::print(std::list<Card> theList) {
	for (auto itr = theList.begin(); itr != theList.end(); itr++) {
		std::cout << *itr << std::endl;
	}
}

void IndexCards::printByIndex() {
	print(cardsByIndex);
}

void IndexCards::printByKeyword() {
	print(cardsByKeyword);
}

std::vector<Card> IndexCards::toVector(std::list<Card> theList) {
	std::vector<Card> vec;
	for (auto itr = theList.begin(); itr != theList.end(); itr++) {
		vec.push_back(*itr);
	}
	return vec;
}

std::vector<Card> IndexCards::getByIndex() {
	return toVector(cardsByIndex);
}

std::vector<Card> IndexCards::getByKeyword() {
	return toVector(cardsByKeyword);
}

void IndexCards::removeCard(std::list<Card>& cards, Card card) {
	for (auto itr = cards.begin(); itr != cards.end(); itr++) {
		if (card == *itr) {
			cards.erase(itr);
			return;
		}
	}
}

void IndexCards::removeCard(Card card) {
	removeCard(cardsByIndex, card);
	removeCard(cardsByKeyword, card);
}