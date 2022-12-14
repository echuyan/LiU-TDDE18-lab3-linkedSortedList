#include <iostream>
#include "sortedLinkedList.h"
#include <string>
#include <initializer_list>


using namespace std;

//------------------------------------CONSTRUCTORS-------------------------------------
	/*default constructor*/
SortedLinkedList::SortedLinkedList() :first{ nullptr }
{
}

/*deep copy constructor = copy each node to the copy*/
SortedLinkedList::SortedLinkedList(SortedLinkedList const& l) : first{ nullptr }
{

	// Comment: Since you are initializing first to nullptr, you don't 
	// need to set it to nullptr again.
	//------------agree, corrected. but we still need to check if it's NOT empty to continue with the algorithm:
	if (!l.empty())
	{
		Node* tmp{};
		Node* tmp1{};
		first = new Node{ l.first->number, l.first->next };

		tmp = first;
		tmp1 = l.first->next;
		while (tmp1 != nullptr)
		{
			tmp->next = new Node{};
			tmp = tmp->next;
			tmp->number = tmp1->number;
			tmp->next = tmp1->next;
			tmp1 = tmp1->next;
		}

	}
}

/*move constructor*/
//shuffling the first pointers;
SortedLinkedList::SortedLinkedList(SortedLinkedList&& l) :first{ l.first }
{
	l.first = nullptr;
}

/*constructor with arbitrary amount of values*/
SortedLinkedList::SortedLinkedList(std::initializer_list<int> list) :first{ nullptr }
{
	{
		for (int i : list)
		{
			insertRecursive(this->first, i);
		}
	}

}

//------------------------------------DESTRUCTOR-------------------------------------

	/*destructor*/
	// go through each node in our list and call delete on them
SortedLinkedList::~SortedLinkedList()
{
	if (!this->empty())
	{
		Node* tmp = first;
		while (tmp != nullptr)
		{
			Node* tmp1 = tmp->next;
			delete tmp;
			tmp = tmp1;
		}
		first = nullptr;
	}
}

//------------------------------------COPY/MOVE OPERATORS-------------------------------------

	/*copy assignment operator (deep copy)*/
	//first delete all items from the destination list and then copy each node
	//
SortedLinkedList& SortedLinkedList::operator= (SortedLinkedList const& l)
{
	//deep copying the source to the destionation using the copy constructor

	SortedLinkedList localcopy{ l };
	std::swap(first, localcopy.first);
	return *this;
}


/*move assignment operator*/
//quick move to an existing object
// TODO: Complementary work needed: Instead of having to empty this list first,
// can you make use of the fact that l will be deconstructed after the assignment
// is done?
// TODO: Complementary work needed: Possible memory leaks. See above TODO.
// TODO: Still possible memory leaks. What if this contains elements? See the above
// TODO hint on how to handle it.
//DONE: The only two ways that we figured out for this problem: either destruct this and shuffle first pointers or clean this and shuffle first pointers
//Here we leave the implementation with the destructor usage. Checked with valgrind, no leaks. Should solve the problem if this is not empty.
//If you meant something else then we are not able to figure out what exactly was meant.
//l
//
// Comment: l, the list your are moving from, will be destructed after the move 
// operation finishes which means you can just swap first between this and l.
//
//
SortedLinkedList& SortedLinkedList::operator= (SortedLinkedList&& l)
{
	this->~SortedLinkedList();
	this->first = l.first;
	l.first = nullptr;
	return *this;
}

//------------------------------------FUNCTIONS-------------------------------------

	/*Simple insert of the value*/
void SortedLinkedList::insert(int const i)
{
	insertRecursive(this->first, i);

}

/*Recursive function for inserting a new node to the list*/

void SortedLinkedList::insertRecursive(Node*& n, int const i)
{

	if (n == nullptr) {
		n = new Node{ i,nullptr };
	}
	else if (n->number >= i)
	{
		Node* tmpNext{ n->next };
		Node* tmp{ new Node{n->number, tmpNext} };
		n->number = i;
		n->next = tmp;
	}
	else
	{
		if (n->next == nullptr)
		{
			n->next = new Node{ i,nullptr };
		}
		else
		{
			insertRecursive(n->next, i);
		}
	}
}



/*Function that removes the node from the list at the given index*/
void SortedLinkedList::remove(int const index)
{
	if (!this->empty() && index > 0 && index <= this->size())
	{
		if (index == 1)
		{
			Node* tmp{ this->first };
			first = first->next;
			delete tmp;
		}
		else
		{
			int i{ 0 };
			Node* tmp{ this->first };
			while (i != index - 2)
			{
				i++;
				tmp = tmp->next;
			}
			Node* tmp1{ tmp->next };
			tmp->next = tmp1->next;

			delete tmp1;
		}
	}
}

/*Functions that returns the value from the list at the given index*/
int SortedLinkedList::access(int const index) const
{

	if (this->empty())
	{
		return -1;

	}
	else
		if (index < 0 || index >= this->size())
		{
			return -1;
		}
		else
		{
			int i{ 0 };
			Node* tmp{ this->first };
			while (i != index)
			{
				tmp = tmp->next;
				i++;
			}
			return tmp->number;
		}
}


/*Function that returns the size of the list*/
int SortedLinkedList::size() const
{
	if (!this->empty())
	{
		int i{ 1 };
		Node* tmp{ this->first };
		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
			i++;
		}
		return i;


	}
	else {
		return 0;
	}
}

/*Function that prints the list*/
void SortedLinkedList::print() const
{
	if (!this->empty())
	{
		Node* tmp{ this->first };
		cout << tmp->number << " ";
		while ((tmp->next) != nullptr)
		{
			tmp = tmp->next;
			cout << tmp->number << " ";

		}
	}
	else {
		cout << "List is empty." << endl;
	}

}


/*Function that checks if the list is empty*/
bool SortedLinkedList::empty() const
{
	return first == nullptr;
}

/*Function that compares two lists by values and size*/
bool SortedLinkedList::operator== (SortedLinkedList& l2) const
{
	if ((this->size()) != (l2.size())) { return false; }
	else
	{
		bool flag{ true };
		Node* tmp1 = this->first;
		Node* tmp2 = l2.first;
		while (tmp1 != nullptr && tmp2 != nullptr && flag != false)
		{
			if (tmp1->number != tmp2->number)
			{
				flag = false;
			}
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		return flag;
	}
}


