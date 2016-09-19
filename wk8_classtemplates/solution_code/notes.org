Tutorial 7 (Week 8)

Class Templates

http://www.cse.unsw.edu.au/~cs6771/15s2/tuts/week8.html

* Q6. Correcting the remove function

- Use std::find_if to find the item in the list and return an iterator.

     http://www.cplusplus.com/reference/algorithm/find_if/

- Use std::vector<T>::erase(it) to erase the item.

     http://www.cplusplus.com/reference/vector/vector/erase/


* Q7 and Q8. Fix to properly remove related work

- Replace relatedWorkLink_ shared_ptr with a weak_ptr

     http://en.cppreference.com/w/cpp/memory/weak_ptr

- Fix Library::ItemContainer::RelatedWork::printItemAndDescription()
  function.


* Q9 and Q10. Fix the duplicate object issue

- Modify Library::add() to detect existing objects.

- Note 1: all the std::find_if() calls that check for existing items
  rely on an equality check of the template item (eg., Book). These
  all rely on the operator==() overloading.

- Note 2: the definition of Book as it stands is brittle. Should
  overload operator!=() otherwise we can get unexpected
  behaviour.


* Q12. Movies: Just duplicate the Book library

- Simply duplicate the Book library.
- Description class is just wrapping std::string. Do we need this?


* Q11. Discussion

- Advantage of an inner class is that the inner class is automatically a
  friend of the outer class and can therefore modify the variables ouf
  the outer class.

- Disadvantage of an inner class is that it can make the code a bit
  unreadable.

- Much of the code requires looping through a vector of items looking
  for a match. This can be expensive.

- Instead consider using std::map/unordered_map or
  (std::set/unordered_set).

      http://www.cplusplus.com/reference/map/map/

      http://www.cplusplus.com/reference/unordered_map/unordered_map/

- std::map is useful if there is a natural < ordering that is
  defined. operator<() must be defined unless the template Compare
  parameter is defined.

- std::unordered_map is useful if there is no natural ordering and a
  hash makes more sense. Relies on a hash function being provided or
  a specialised from std::hash<T>{}.

      namespace std
      {
         template<> struct<MyKey>{ std::size_t operator()(const MyKey& k) const; };
      }

- Note omision in C++11 that something like the boost::hash_combine()
  function is not provided.

    http://stackoverflow.com/questions/7222143/unordered-map-hash-function-c



* Making Templates Better: "Concepts" the future of C++ templates.

- Working with templates can be very difficult. You end up spending a
  lot of time trying to understand compiler error messages.

- Clang typically does a better job than GCC with error messages, but
  ultimately the problem is with the language and not the compiler.

- The problem is that currently there is no easy way to specify what
  is an appropriate type for a given template parameter. Instead the
  compiler has to instantiate the template and try to compile it. If
  something is wrong (e.g., a missing function overload) then there
  will be an error message generated from somewhere deep in the
  template code.

- What is needed is a mechanism to specify required properties of a
  template parameter. The compiler could generate a sensible error
  message reporting that the parameter doesn't satisfy some property.

- In C++ speak these properties are called "Concepts".

     https://en.wikipedia.org/wiki/Concepts_%28C%2B%2B%29

- Unfortunately, Concepts didn't make it into C++11. Hopefully, C++17
  will include a version called "Concepts-lite":

     http://stackoverflow.com/questions/15669592/what-are-the-differences-between-concepts-and-template-constraints

- In the meantime you have to live with the pain of uninformative
  compiler errors :(

- What this also means is that you should be sparing when writing your
  own templates if you think other people will need to use them (for
  example in a library).


