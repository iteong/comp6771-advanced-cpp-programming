#include <iostream>
#include <vector>

// give the two templates
// need to write the variadic template
// need to explain what is going on.

void test_main_tute();
void test_function_overloads();
void test_variadic_templates();

//----------------------------------------------------------------------
// Function template printIfWholeNumber() and specilisation for
// int. Outputs true if the type is int and false otherwise.
// ----------------------------------------------------------------------

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

//----------------------------------------------------------------------
// Function template printAndCountWholeNumbers.
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Single argument version
//----------------------------------------------------------------------

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

//----------------------------------------------------------------------
// Variadic argument version
//----------------------------------------------------------------------

template <typename T, typename... U>
unsigned int printAndCountWholeNumbers(T head, U... tail)
{
	unsigned int count = printAndCountWholeNumbers(head);
	count += printAndCountWholeNumbers(tail...);
	return count;
}

//----------------------------------------------------------------------
// Overload for std::vector<T>
//----------------------------------------------------------------------

template <typename T>
unsigned int printAndCountWholeNumbers(const std::vector<T>& vd)
{
	unsigned int count = 0;
	for (auto d : vd)
    {
		auto dCopy = d;
        // work out if d is a whole number
		dCopy -= static_cast<int>(d);
		if (dCopy == 0)
        {
            // call: printIfWholeNumber and add to count.
			count += printIfWholeNumber(static_cast<int>(d));
			std::cout << " ";
		}
	}
	return count;
}

//----------------------------------------------------------------------
// the main tutorial question
//----------------------------------------------------------------------

void test_main_tute()
{
	// why does 7.0 not get printed?
	auto c = printAndCountWholeNumbers(1, 2.5, 3, 4.5, 5.5, 6, 7.0, -5, "2");
	std::cout << "count = " << c << std::endl;


	// why does 32 print this time?
	std::vector<double> d = {1.2, 32.0, 3.2, 5.30, 5.4, 6, -5};
	auto dc = printAndCountWholeNumbers(d);
	std::cout << "count = " << dc << std::endl;

	std::vector<unsigned int> vui = { 65, 343, 21, 3};
	dc = printAndCountWholeNumbers(vui);
	std::cout << "count = " << dc << std::endl;

    // Note: this will compile if the printAndCouldWholeNumbers()
    // overload for std::vector<T> is not defined (although the count
    // will be 0). However it won't compile when the overload is
    // defined.
//	std::vector<std::string> vs = { "1", "2" , "3", "4"};
//	dc = printAndCountWholeNumbers(vs);

}

//----------------------------------------------------------------------
// main
//----------------------------------------------------------------------

int main()
{
    test_main_tute();
//    test_function_overloads();
//    test_variadic_templates();
}

//----------------------------------------------------------------------
// Some extra stuff
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// Basic of template function overloading/specialisation
// 5 versions of func3 - which one is called in what circumstances?
//----------------------------------------------------------------------

// V1: Template function
template<typename T, typename U>
void func3(const T& t, const U& u)
{
    std::cout << "V1: template func3<T, U>: " << t << " "
              << u << std::endl;
}

// V2: Specialisation of template - specialisation of V1
template<>
void func3<int, std::string>(const int& t, const std::string& u)
{
    std::cout << "V2: specialisation func3<int, std::string>: "
              << t << " " << u << std::endl;
}

// V3: Overloaded template function
template<typename U>
void func3(const int& t, const U& u)
{
    std::cout << "V3: overload template func3<U>: "
              << t << " " << u << std::endl;
}

// V4: Specialisation of overloaded template function
template<>
void func3<std::string>(const int& t, const std::string& u)
{
    std::cout << "V4: specialisation func3<std::string>: "
              << t << " " << u << std::endl;
}

// V5: Overloaded (non-template) function
void func3(const int& t, const std::string& u)
{
    std::cout << "V5: overloaded non-template func3: "
              << t << " " << u << std::endl;
}

//----------------------------------------------------------------------
// Testing the different versions of func3: template, template
// specialisation, template overloading, and overloading.
// ----------------------------------------------------------------------

void test_function_overloads()
{
    int i = 9;
    std::string s = "a";

    func3(i, s);                    // V5 is called - if no V5 then V4 is called
                                    //                if no V5 & V4 then V3 is called.
                                    //                if no V5, V4, V3 then V2 is called.

                                    // force specific template version

    func3<int,std::string>(i, s);   // V2 is called - if no V2 then V1 is called

    func3<std::string>(i,s);        // V4 is called - if no V4 then V3 is called
                                    //              - if no V4 and V3 then compiler error!

                                    // Force a template version (but compiler decides which)

    func3<>(i, s);                  // V4 is called - if no V4 then V3 is called
                                    //              - if no V4 and V3 then V2 is called

    // NOTE: function matching happens before any implicit type conversion!!!

    func3(9, "a");                  // V3 (not V4) is called because "a" is const char*.
    func3(9U, "a");                 // V1 is called because 9U is not int.

    // Of course you can static cast to ensure you have the desired
    // type - which has its own risks.
    func3(static_cast<int>(9U), static_cast<std::string>("a"));
}


//----------------------------------------------------------------------
// Some variadic template stuff.
// - func1 simply shows how it works
// - func2 shows how template instantiation rules allow recursive
//   behaviour.
//----------------------------------------------------------------------


template<typename... Args>
void func1(Args... args)
{
    std::cout << "func1 of size: " << sizeof...(args) << std::endl;
}

template<typename Head>
bool func2(Head h)
{
    std::cout << "func2 non-variadic" << std::endl;
    return true;
}

template<typename Head, typename... Tails>
bool func2(Head h, Tails... ts)
{
    std::cout << "func2 of size: " << sizeof...(ts) + 1 << std::endl;
    return func2(h) && func2(ts...);
}

void test_variadic_templates()
{
    std::cout << "Test1 size of variadic template instantiation" << std::endl;
    func1();
    func1(1.0);
    func1(1.0, 5);

    std::cout << "Test2 size of variadic template instantiation" << std::endl;
//    func2();             // compiler error
    auto b1 = func2(1.0);            // NOTE: this calls the non-variadic version only
    auto b2 = func2(1.0, 5, 5.6);    // Calls the variadic version

    std::cout << "B1: " << b1 << std::endl;
    std::cout << "B2: " << b2 << std::endl;
}
