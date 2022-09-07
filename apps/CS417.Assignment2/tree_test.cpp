#include "gtest/gtest.h"
#include "pch.h"
#include "Tree.h"
#include <stdlib.h>
#include <set>

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
