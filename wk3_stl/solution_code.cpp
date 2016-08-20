#include <vector>
#include <array>
#include <list>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

#include <initializer_list>


int main(int args, char* argv[])
{

/*
       // C++98 way:

    const char* fixed[] = { "one", "two", "three" };

    // Note: sizeof(array) only works when array is not a parameters.
    // For parameter arrays must also send a size parameter.
    std::size_t numelements = sizeof(fixed)/sizeof(fixed[0]);

//    std::vector<std::string> strvec(fixed, fixed+numelements);

    // alternative - std::vector<std::string> strvec = {"one", "two", "three"};

    */

    std::vector<std::string> strvec({"one", "two", "three"});

/*
    std::cout << "strvec before sort: ";
    for (const std::string& s : strvec) std::cout << s << " ";
    std::cout << std::endl;
*/
//    std::sort(strvec.begin(), strvec.end());
//    std::sort(&strvec[0], &strvec[1]);

//    strvec.push_back("four");

/*
    std::cout << "strvec after sort: ";
    for (const std::string& s : strvec) std::cout << s << " ";
    std::cout << std::endl;
*/


    // The array version
    std::array<int, 3> intarr = { {3, 2, 1} };

//    std::sort(intarr.begin(), intarr.end());

    // The list version
    std::list<int> intlist;


    // Many different ways to copy the list to the intlist
    // 1: Tute requirement: explicit std::back_insert_iterator and insert using iterators.


/*
    std::back_insert_iterator<std::list<int> > back_it(intlist);

    for (auto it = intarr.begin(); it != intarr.end(); ++it)
    {
        *back_it = *it;
    }
*/

    // 2: explicit std::back_insert_iterator and std::copy

//    std::back_insert_iterator<std::list<int> > back_it(intlist);
//    std::copy(intarr.begin(), intarr.end(), back_it);

    // 3: use std::back_inserter and std::copy
//    std::copy(intarr.begin(), intarr.end(), std::back_inserter(intlist));

    // 4: range based for loop with push_back.
    for (int i : intarr) intlist.push_back(i);

    intlist.sort();
/*
    std::cout << "intlist: ";
    for (int i : intlist) std::cout << i << " ";
    std::cout << std::endl;
    return 1;
*/
/*

    std::cout << "intlist: ";
    for (int i : intlist) std::cout << i << " ";
    std::cout << std::endl;

*/

    std::map<std::string, int> map_to_int;

    // Note 1: the use of the safer (C++11) cbegin(), cend()
    // Note 2: alternative use std::make_pair()

    std::vector<std::string>::const_iterator k;

    int j = 0;
    for (auto k = strvec.cbegin(); k != strvec.cend(); ++k)
    {
        map_to_int[*k] = j++;
//        map_to_int.insert( std::pair<std::string, int>(*k, j++));
//        map_to_int.insert( std::make_pair(*k, j++));

    }


    for (const auto &p: map_to_int)
    {
        std::cout << p.first << ": " << p.second << std::endl;
    }

}