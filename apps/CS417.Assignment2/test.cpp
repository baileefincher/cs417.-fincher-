#include "pch.h"
#include "index_card.h"
#include "organizing_list.h"
#include "Tree.h"

#include <vector>

using namespace std;

TEST(OrganizingListTest, Test) {
	SelfOrganizingList<int> lst;

	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);
	lst.push_back(4);

	ASSERT_EQ(4, lst.size());
	auto itr = lst.begin();
	ASSERT_EQ(1, *itr++);
	ASSERT_EQ(2, *itr++);
	ASSERT_EQ(3, *itr++);
	ASSERT_EQ(4, *itr++);

	lst.moveToFront(3);
	itr = lst.begin();
	ASSERT_EQ(3, *itr++);
	ASSERT_EQ(1, *itr++);
	ASSERT_EQ(2, *itr++);
	ASSERT_EQ(4, *itr++);

	lst.moveToFront(4);
	itr = lst.begin();
	ASSERT_EQ(4, *itr++);
	ASSERT_EQ(3, *itr++);
	ASSERT_EQ(1, *itr++);
	ASSERT_EQ(2, *itr++);
}

class IndexCardTest : public ::testing::Test {
protected:
	IndexCards* cards;

	void SetUp() override {
		cards = new IndexCards();
		cards->insert(Card(4, "B"));
		cards->insert(Card(1, "D"));
		cards->insert(Card(3, "C"));
	}

	void TearDown() override {
		delete cards;
	}

};

TEST_F(IndexCardTest, TestInsert) {

	vector<Card> byIndex = cards->getByIndex();
	ASSERT_EQ(3, byIndex.size()) << "Testing";
	auto itr = byIndex.begin();

	ASSERT_EQ(1, (*itr).getIndex());
	ASSERT_EQ("D", (*itr).getKeyword());
	itr++;

	ASSERT_EQ(3, (*itr).getIndex());
	ASSERT_EQ("C", (*itr).getKeyword());
	itr++;

	ASSERT_EQ(4, (*itr).getIndex());
	ASSERT_EQ("B", (*itr).getKeyword());

	vector<Card> byKeyword = cards->getByKeyword();
	ASSERT_EQ(3, byKeyword.size());
	itr = byKeyword.begin();

	ASSERT_EQ(4, (*itr).getIndex());
	ASSERT_EQ("B", (*itr).getKeyword());
	itr++;

	ASSERT_EQ(3, (*itr).getIndex());
	ASSERT_EQ("C", (*itr).getKeyword());
	itr++;

	ASSERT_EQ(1, (*itr).getIndex());
	ASSERT_EQ("D", (*itr).getKeyword());
}

TEST_F(IndexCardTest, TestDelete) {
	cards->removeCard(Card(3, "C"));

	vector<Card> byIndex = cards->getByIndex();
	ASSERT_EQ(2, byIndex.size());
	auto itr = byIndex.begin();

	ASSERT_EQ(1, (*itr).getIndex());
	ASSERT_EQ("D", (*itr).getKeyword());
	itr++;

	ASSERT_EQ(4, (*itr).getIndex());
	ASSERT_EQ("B", (*itr).getKeyword());

	vector<Card> byKeyword = cards->getByKeyword();
	ASSERT_EQ(2, byKeyword.size());
	itr = byKeyword.begin();

	ASSERT_EQ(4, (*itr).getIndex());
	ASSERT_EQ("B", (*itr).getKeyword());
	itr++;

	ASSERT_EQ(1, (*itr).getIndex());
	ASSERT_EQ("D", (*itr).getKeyword());
}

TEST(TreeTest, Test) {
	// Code referenced from https://cplusplus.com/reference/cstdlib/rand/
	Tree<int> tree;

	srand(time(NULL));
	std::set<int> integers;

	for (int i = 0; i < 1000; i++) {
		int x = rand();
		integers.emplace(x);
		tree.insert(x);
	}

	// now search for the inserted integers
	for (int i : integers) {
		ASSERT_TRUE(tree.search(i));
	}
}
