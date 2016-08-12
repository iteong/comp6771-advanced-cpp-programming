/*
q1.cpp
week 3 tutorial 2
Callum Howard
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <initializer_list>
#include <algorithm>
#include <list>
#include <iterator>
#include <string> // string is a common data structure so other libs will have it but always include
#include <map>
#include <utility> // std::pair


int main()
{

	// move semantic, just going to point to object created, not object created on the left
	// when using auto, needs to initialize container
	auto nums_v = std::vector<std::string>{"one", "two", "three"}; // modern way and using initializer list

	// old way of initializing vector:
	// std::vector<std::string> nums_v;
	// nums_v.push_back("one");
	// nums_v.push_back("two");
	// nums_v.push_back("three");

	for (const auto& e : nums_v) { std::cout << e << " "; }
	std::cout << std::endl;

	// std::sort algorithm needs random access and swap from one index to any other random index, while list.sort() uses a linked list to compare and sort
	std::sort(begin(nums_v), end(nums_v)); // sort can have 3rd argument as ascending and descending

	for (auto it = std::cbegin(nums_v); it != std::cend(nums_v); ++it) { // cbegin = iterator is NOT const, but point to elements that are const, READ ONLY
	// for (auto it = nums_v.begin(); it != nums_v.end(); ++it) { ===> disadvantage: can't use overloading for the template specialization, no need to modify class or inherit class to get begin and end
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	// array: needs to have size of array at declaration time, unlike vectors
	auto nums_a = std::array<int, 3>{{3,2,1}}; // () can be {} as well = tell them u want to initialize something first {}, then list {}
	

	std::sort(begin(nums_a), end(nums_a)); // sort can have 3rd argument as ascending and descending

	for (auto it = std::cbegin(nums_a); it != std::cend(nums_a); ++it) { // cbegin = iterator is NOT const, but point to elements that are const, READ ONLY
	// for (auto it = nums_a.begin(); it != nums_a.end(); ++it) { ===> disadvantage: can't use overloading for the template specialization, no need to modify class or inherit class to get begin and end
		std::cout << *it << " ";
	}
	std::cout << std::endl;


	// list time
	auto nums_l = std::list<int>{{3,1,2}};
	nums_l.sort();

	for (const auto& e : nums_l) { std::cout << e << " "; }
	std::cout << std::endl;

	auto bii = std::back_insert_iterator<decltype(nums_l)>{nums_l}; // decltype finds out what is the type and replaces expression with actual type
	// normaul way is use <std::list<int> >{nums_l}

	// can also be this instead of for loop => std::copy(begin(nums_a), end(nums_a), bii);
	for (const auto& e : nums_a) { // go over int array to get values to map into int list
		*bii = e;
	}

	// map time, maps implemented as red-black trees for normal map
	auto nums_m = std::map<std::string, int>{};

	// struct pair {
	// 	int first, second;
	// }

	auto p1 = std::make_pair("one", 2);
	nums_m.insert(p1);
	// or nums_m.insert(std::make_pair("one", 1));
	// can also use nums_m["four"] = 42;
	// p1.first = "one" and p1.second = 2;


return 0;
}


