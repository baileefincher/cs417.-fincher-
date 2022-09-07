#include "gtest/gtest.h"
#include "index_card.h"

using namespace std;

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

/*
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
*/
