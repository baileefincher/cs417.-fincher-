#pragma once

#include <memory>
#include <iostream>

template<typename T>
class TreeNode {
public:
	TreeNode(T t) :
		t(t) {
	}

	~TreeNode() {
	}

	T getT() {
		return t;
	}

	TreeNode<T>* getLeft() {
		return left.get();
	}

	TreeNode<T>* getRight() {
		return right.get();
	}

	void setLeft(TreeNode<T>* ptr) {
		left = std::unique_ptr<TreeNode<T>>(ptr);
	}

	void setRight(TreeNode<T>* ptr) {
		right = std::unique_ptr<TreeNode<T>>(ptr);
	}

private:
	T t;
	std::unique_ptr<TreeNode<T>> left;
	std::unique_ptr<TreeNode<T>> right;
};

template<typename T>
class Tree {
private:
	std::unique_ptr<TreeNode<T>> head;

	void insert(TreeNode<T>* tree, T t) {
		if (t < tree->getT()) {
			if (tree->getLeft() == NULL) {
				tree->setLeft(new TreeNode<T>(t));
			}
			else {
				insert(tree->getLeft(), t);
			}
		}
		else if (tree->getRight() == NULL) {
			tree->setRight(new TreeNode<T>(t));
		}
		else {
			insert(tree->getRight(), t);
		}
	}

	void print(TreeNode<T>* tree) {
		if (tree->getLeft() != NULL) {
			print(tree->getLeft());
		}
		std::cout << tree->getT() << ", ";
		if (tree->getRight() != NULL) {
			print(tree->getRight());
		}
	}

	bool search(TreeNode<T>* tree, T t) {
		if (tree == NULL) {
			return false;
		}

		if (tree->getT() == t) {
			return true;
		}

		TreeNode<T>* left = tree->getLeft();
		if (left != NULL && t < tree->getT()) {
			return search(left, t);
		}

		TreeNode<T>* right = tree->getRight();
		if (right != NULL && t > tree->getT()) {
			return search(right, t);
		}

		return false;
	}

public:

	void insert(T t) {
		if (head == NULL) {
			head = std::unique_ptr<TreeNode<T>>(new TreeNode<T>(t));
		}
		else {
			insert(head.get(), t);
		}
	}

	void print() {
		if (head != NULL) {
			print(head.get());
		}
	}

	bool search(T t) {
		if (head.get() == NULL) {
			return false;
		}

		return search(head.get(), t);
	}

};