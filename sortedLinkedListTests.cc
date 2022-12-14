#include "catch.hpp"
#include "sortedLinkedList.h"

		

TEST_CASE("insert")
{
		//checking insertion to a non-empty list
		SortedLinkedList l1{ 2,1,3,10};
		l1.insert(55);
		l1.insert(0);
		SortedLinkedList l1_check{ 0,2,1,3,10,55};
		REQUIRE ((l1==l1_check));



		//checking insertion to an empty list
		SortedLinkedList l2{ };
		REQUIRE(l2.empty());
		l2.insert(55);
		SortedLinkedList l2_check{55};
		REQUIRE ((l2==l2_check));
}


TEST_CASE("remove")
{
		SortedLinkedList l1{ 2,1,3,10};
		
		//removing the first element
		l1.remove(1);
		REQUIRE(((l1.access(3) == -1) && (l1.size() == 3)));
		SortedLinkedList l2_check{ 2,3,10 };
		REQUIRE((l1 == l2_check));

		//removing the element in the middle
		l1.remove(2);
		REQUIRE (( (l1.access(3)==-1) && (l1.size()==2) ));
		SortedLinkedList l1_check{ 2,10};
		REQUIRE ((l1==l1_check));

		//removing the last element
		l1.remove(2);
		REQUIRE(((l1.access(2) == -1) && (l1.size() == 1)));
		SortedLinkedList l3_check{ 2 };
		REQUIRE((l1 == l3_check));
		
		
}

TEST_CASE("access")
{
		
		SortedLinkedList l1{ 2,1,3,10};
		CHECK ((l1.access(2)==3));
		
		//checking boundaries
		CHECK ((l1.access(3)==10));
		CHECK ((l1.access(0)==1));
		//checking out of the boundaries
		CHECK ((l1.access(-1)==-1));
		CHECK ((l1.access(15)==-1));
		//checking empty list
		SortedLinkedList l2{  };
		CHECK ((l2.access(0)==-1));
}

TEST_CASE("empty")
{
		SortedLinkedList l1{ 2,1,3,10};
		CHECK_FALSE((l1.empty()));
		SortedLinkedList l2{  };
		CHECK ((l2.empty()));
}

TEST_CASE("size")
{
		SortedLinkedList l1{ 2,1,3,10};
		CHECK ((l1.size()==4));
		SortedLinkedList l2{  };
		CHECK ((l2.size()==0));
}


TEST_CASE("default constructor")
{
   		SortedLinkedList l1{  };
		REQUIRE(l1.empty());
}

TEST_CASE( "copy constructor" ) {
		
		//non-empty
		SortedLinkedList l2{ 2,1,3,10,42,41,55,54,6,9,7,11,22 };
		SortedLinkedList l3{ l2 };
		REQUIRE ((l2==l3));
		//empty
		SortedLinkedList l7{};
		SortedLinkedList l8{ l7 };
		REQUIRE ((l7==l8));
		REQUIRE ((l8.empty()));
}


TEST_CASE( "constructor from list of values" ) {
 
		//checking non-empty list creation
		SortedLinkedList l1{ 2,1,3,10};
		CHECK (((l1.access(0)==1)&&(l1.access(1)==2)&&(l1.access(2)==3)&&(l1.access(3)==10)));
		
		//checking empty list creation
		SortedLinkedList l2{  };
		REQUIRE(l2.empty());
}


TEST_CASE( "destructor" ) {
		SortedLinkedList l1{ 2,1,3,10};
		REQUIRE((l1.size()==4));
		l1.~SortedLinkedList();
		REQUIRE((l1.empty()));
}


TEST_CASE( "operator= (copy)" ) {
		//non-empty
		SortedLinkedList l5{ 2,0,3 };
		SortedLinkedList l6{ 10,32,15 };
		REQUIRE_FALSE((l5==l6));
		l6 = l5;
		REQUIRE((l5==l6));
		
		//empty
		SortedLinkedList l9{};
		SortedLinkedList l10{ 10,32,15 };
		REQUIRE_FALSE((l10==l9));
		l10 = l9;
		REQUIRE((l10.empty()));
		REQUIRE((l10==l9));
}


TEST_CASE( "operator= (move)" ) {
		
		SortedLinkedList l1{ 2,0,3 };
		SortedLinkedList l2{  };
		REQUIRE_FALSE((l1.empty()));
		l2 = std::move(l1);
		REQUIRE((l1.empty()));
		SortedLinkedList l10{ 2,0,3 };
		REQUIRE((l2 == l10));
}

TEST_CASE( "operator== (compare)" ) {
		//non-empty equal
		SortedLinkedList l11{ 2,0,3 };
		SortedLinkedList l12{ 2,0,3 };
		REQUIRE((l11==l12));
		//non-empty of different length
		SortedLinkedList l13{ 2,0,3 };
		SortedLinkedList l14{ 2,0,3,4 };
		REQUIRE_FALSE((l13==l14));
		//non-empty unequal
		SortedLinkedList l15{ 2,0,3 };
		SortedLinkedList l16{ 2,1,3 };
		REQUIRE_FALSE((l15==l16));
		//empty
		SortedLinkedList l17{};
		SortedLinkedList l18{};
		REQUIRE((l17==l18));
}
