Tutorial 6:

http://www.cse.unsw.edu.au/~cs6771/15s2/tuts/week7.html

- Function Template Specialisation
- Variadic Function Templates
- Wrapper around std::unique_ptr

* Tute Question 1:

** Part 1: printIfWholeNumber()

    template <typename T>
    bool printIfWholeNumber(const T&)
    {
	return false;
    }

    template <>
    bool printIfWholeNumber<int>(const int& i)
    {
	std::cout << i;
	return true;
    }

- Q: What will this template do if it is given a std::string, a
  double, or a EuclideanVector?

  The general version will be called.

- Q: What will this template do if it is given an int?

  The specialisation will be called.

- Q: What will this template do if it is given a long?

  The general version will be called.


** Part 2: printAndCountWholeNumbers() - basic version

   template <typename T>
   unsigned int printAndCountWholeNumbers(const T& d)
   {
	if (printIfWholeNumber(d))
        {
		std::cout << " ";
		return 1;
	}
	return 0;
   }

- Q: What will this template do if it is given a std::string, a
  double, or a EuclideanVector? What will this template do if it is
  given an int? What will this template do if it is given a long?

  In all cases will call the appropriate printIfWholeNumber()
  function.


** Part 3: printAndCountWholeNumbers() - variadic template

    template <typename T, typename... U>
    unsigned int printAndCountWholeNumbers(T head, U... tail)
    {
	unsigned int count = printAndCountWholeNumbers(head);
	count += printAndCountWholeNumbers(tail...);
	return count;
    }

- Test your code by writing a main function that contains:

    auto c = printAndCountWholeNumbers(1, 2.5, 3, 4.5, 5.5, 6, 7.0, -5, "2" );
    std::cout << "count = " << c << std::endl;


- Q: The numbers 1 3 6 -5 should be printed out. Why is the number 7
  not printed? Why is the number 2 not printed?

  7 and 2 don't fit the specialisation of printIfWholeNumber<int>() as
  7.0 is a float and "2" is a string.


** Part 4: printAndCountWholeNumbers() - std::vector<X> overload

- Consider:

    std::vector<double> d = {1.2, 32.0, 3.2, 5.30, 5.4, 6, -5};
    auto dc = printAndCountWholeNumbers(d);
    std::cout << "count = " << dc << std::endl;

    std::vector<unsigned int> vui = {65, 343, 21, 3};
    dc = printAndCountWholeNumbers(vui);
    std::cout << "count = " << dc << std::endl;

- Q: Why won't it print out the correct number of whole numbers in
  either vector?

  The variadic template function is not called. Only the the single
  parameter template version is called with the std::vector<T>
  object. std:vector<T> is treated as a single object when passed to
  printIfWholeNumber().

- The provided std::vector<X> template overloaded version of the
  function handles the vector cases.

- Q: In this function the number 32 gets printed, why?

  The overload for std::vector<T> for the case of std::vector<double>
  is casting each element to an int. If the element can be static_cast
  to an int without any loss of precision then the static_cast version
  is printed. Therefore '32.0' is treated as '32'.

- BIG NOTE: The following fails to compile with the new std::vector<T>
  template overload but succeeds without the overload. Why?

    std::vector<std::string> vs = { "1", "2" , "3", "4"};
    dc = printAndCountWholeNumbers(vs);

  The reason is that the std::vector<T> version matches correctly
  (with T=std::string) so the template gets instantiated. However, it
  then has a compiler error because std::string can't be static_cast
  to int.

  Without the the std::vector<T> version then the "const T& d" version
  is matched. This compiles without error because it treats the vector
  as a single object (that is not a whole number).




* Tute Question 2:

** Part 1: Template to return a unique_ptr copy

- Add the following template function:

     template <typename T>
     std::unique_ptr<T> make_unique(T t) {
	 return std::unique_ptr<T>(new T(t));
     }

- This function will create a copy of the data passed into it on the
  heap and return a unique_ptr object around the data.

- Add the following code to a main function to test this:

     auto dptr = make_unique(3.14);
     std::cout << *dptr << std::endl;

- Now try to add to the main function:

     auto dptr2 = make_unique(dptr);
     std::cout << *dptr2 << std::endl;

- Q: This won't compile as you can't copy construct a unique_ptr. Why?

  - The template is being instantiated as:

      std::unique_ptr<std::unique_ptr<double> >
      make_unique(std::unique_ptr<double> t)
      {
	     return std::unique_ptr<
                 std::unique_ptr<double> >(new std::unique_ptr<double>(t));
       }

  There are many problems:

  - Problem 1:

    The copy constructor for unique_ptr is deleted in order to
    guarantee single ownership of the underlying object. There are two
    potential uses of a copy constructor in this instantiation:

    - 1) In the parameter list std::unique_ptr is passed by
         value. This is only possible when using the move constructor.

     - 2) When creating the new object the copy constructor is used.

  - Problem 2:

    Note also that there is no defined stream output operator that
    takes: std::unique_ptr<std::unique_ptr<double>>

    Hence the print output line would need to be changed to:

    std::cout << **dptr2 << std::endl

  - Problem 3:

    Even if we create a special version that uses std::move(), it is
    no longer making of copy of the object. The original object is
    no-longer valid. Accessing the original should seg-fault.

      make_unique(std::unique_ptr<double> t)
      {
	     return std::unique_ptr<
                 std::unique_ptr<double> >(new std::unique_ptr<double>(std::move(t)));
       }

- NOTE: See the code from Tute 5 for discussion on when it is
  appropriate to pass unique_ptr to functions.


** Part 2: Returning the underlying object

- Consider the following function templates:

     template <typename T>
     T getBase(T t) {
	 return t;
     }

     template <typename T>
     auto getBase(T *t) -> decltype(*t) {
	 return *t;
     }

- Q: What do these functions do?

  The functions return the base object irrespective of whether it is a
  pointer or not.

- Add the following code to your main method to test them:

     int i = 9;
     int* iptr = &i;
     std::cout << getBase(i) << std::endl;
     std::cout << getBase(iptr) << std::endl;

- Now add to main:

      std::cout << getBase(dptr) << std::endl;

- Q: Why does this not compile? Can you write a third overloaded
  function template that will get the base type from the unique_ptr?

  While a smart pointer acts like a normal pointer (by overloading *
  and ->) it is not a real pointer. Hence the pointer overloaded
  getBase is NOT being instantiated for the unique_ptr<double>
  object. Instead the general version is being instantiated. Besides
  producing the wrong behaviour it would also require std::move() to
  work. e.g.,  std::cout << *getBase(dptr) << std::endl;

  

* Function template specialisation and overloading

  - 1: function template:

       template<typename T, typename U>
       void func3(const T& t, const U& u);

  - 2: specialisation of function template (1):

       template<>
       void func3<int, std::string>(const int& t, const std::string& u);

- Partial function template specialisation is not allowed (note: it is
  allowed for class templates).

- But functions have overloading!

- Note: there is a difference between template specialisation and
  template overloading.

  - 3: overloaded function template:

       template<typename U>
       void func3(const int& t, const U& u);

  - 4: specialisation of overloaded function template (3):

       template<typename U>
       void func3<std::string>(const int& t, const U& u);

  - 5: overloaded (non-template) function:

       void func3(const int& t, const std::string& u);

- There are many scenarios in which the different func3 versions will
  be called (see the sample code in variadicPrint). Some basics:

  - Function matching happens before implicit type conversions.
  - Match to function version with least number of template parameters
    (ignoring specialisations).
  - Match a specialisation before the general version of a template.

- For more details on the rules that determine which version of a
  function gets applied see:

     http://www.gotw.ca/publications/mill17.htm

- The lesson :) - it's easy to shoot yourself in the foot. Keep it
  simple and don't do tricky things unless you really have to!


* Variadic Templates - some basics

 - New in C++11

- A template that can take an arbitrary number of template arguments
  of any type. For example:

    template<typename... Args> void Func(Args... params)
    {
      // do something ...
    }

- "typename... Args" is the template parameter pack
- "Args...params" is the function parameter pack.

- Things to note:

  - You do not have direct access to the list of types and
    arguments.

  - Because of template instantiaton rules if a non-variadic version
    exists then it will be instantiated instead of the variadic
    version. This is the main feature that allows for recursion.

       template<typename T>
       bool func2(T t) { std::cout << t << std::endl; return true; }

       template<typename H, typename... Ts>
       void func2(H h, Ts... ts)
       {
          return func2(h) && func2(ts...);
       }

  - This all happens at the compiler level so there is no runtime
    recursion within the compiled code.

- Lots of sources of information, but I couldn't find something really
  good and concise. So here are a couple:

  - http://eli.thegreenplace.net/2014/variadic-templates-in-c/

  - https://thenewcpp.wordpress.com/2011/11/23/variadic-templates-part-1-2/


* More advanced templates: for those that are interested

- As was observed in Q1 the template (and its specialisation) for
  printIfWholeNumber() does not perform as one might intuitively hope
  for non-int integer types (such as long and unsigned int). To make
  it robust you would need to provide explicit specialisations for
  each of these other integer types.

-  Alternatively, you could use template overloading and type traits
  and std::enable_if. For example the following replacement
  definitions distinguish between integral and non-integral datatypes.

     template <typename T,
               typename std::enable_if<std::is_integral<T>::value, T>::type* = nullptr>
     bool printIfWholeNumber(const T& i)
     {
	std::cout << i;
	return true;
     }

     template <typename T,
               typename std::enable_if<!std::is_integral<T>::value, T>::type* = nullptr>
     bool printIfWholeNumber(const T& i)
     {
        return false;
     }

 - How this works.

   - std::is_integral<T> and std::enable_if are defined in
     <type_traits> header. They are type traits that are evaluated at
     compile time (so no runtime overhead). These type traits rely on
     a property of C++ compilation called SFINAE (Substitution Failure
     Is Not An Error).

    - std::is_integral<T>::value evaluates to true if T is an integral
      value (int, long signed unsigned, bool, char) and false
      otherwise.

    - std::enable_if<bool, T> takes a boolean and a type T. If the
      boolean is true then the instantiation of std::enable_if<bool,
      T>::type will have a valid typedef named 'type'. Otherwise it will
      not be defined. If it is not defined then the instantiated
      template will not be well-formed C++. However, because of SFINAE
      this will simply mean that the template will not be instantiated
      for this type.

    - E.g. For type 'int' which is an integral type:

           T = int,

           std::is_integral<T>::value = true, hence

           std::enable_if<std::is_integral<T>::value, T>::type = T = int.

      This leads to the well-formed template instantiation:

           template <int, int* = nullptr>
           bool printIfWholeNumber(const int& i)
           {
	      std::cout << i;
	      return true;
           }

      Note: int* = nullptr is well-formed but has no other use.

      Considering the other template:

          std::is_integral<T>::value = true, so

          !std::is_integral<T>::value = false,

      Hence,

           std::enable_if<!std::is_integral<T>::value, T>::type

      is syntactically invalid code because the typedef 'type' is not
      defined. In effect the template is instantiated to:

           template <int, * = nullptr>
           bool printIfWholeNumber(const int& i)
           {
	      std::cout << i;
	      return true;
           }

      Because of SFINAE this is not a compiler error and instead
      simply means that the template is not instantiated for this
      particular type.

      Hence for every type (which corresponds to a call to the
      function) one and only one of the two overloaded templates is
      instantiated, and we get the desired behaviour.

- See following for more details:

  http://eli.thegreenplace.net/2014/sfinae-and-enable_if/

