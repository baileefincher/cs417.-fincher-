#include "organizing_list.h"
#include <string>
#include "gtest/gtest.h"
#include "pch.h"

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
