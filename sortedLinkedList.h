#ifndef SORTEDLINKEDLIST_H
#define SORTEDLINKEDLIST_H
#include <initializer_list>


class SortedLinkedList {

private:
	struct Node
	{
		int number{ 0 };
		Node* next{ nullptr };

	};
	Node* first{nullptr};
	void insertRecursive(Node*& n, int const i);

public:
        SortedLinkedList(); //default constructor
	SortedLinkedList(SortedLinkedList const& l); //copy constructor
	SortedLinkedList(SortedLinkedList&& l); //move constructor
	SortedLinkedList(std::initializer_list<int> list); //	constructor with arbitrary amount of values

	~SortedLinkedList(); //destructor

	SortedLinkedList& operator= (SortedLinkedList const& l); //copy assignment operator
	SortedLinkedList& operator= (SortedLinkedList&& l); //move assignment operator

	bool operator== (SortedLinkedList& l2) const;//comparison by values for two lists
	void insert(int const i);//insert the given value to the list
	void remove(int const index);//remove the element at the given index
	int access(int const index) const;//access the element at the given index
	void print() const;
	bool empty() const;
	int size() const;
};

#endif
