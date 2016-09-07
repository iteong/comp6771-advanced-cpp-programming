#ifndef SUPPORT_HPP
#define SUPPORT_HPP

//----------------------------------------------------------------------
// Check for known compiler C++11 issue of compilers not supporting
// std::vector<T>::erase(const_iterator).
// ----------------------------------------------------------------------

#if defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__GNUC_PATCHLEVEL__)
#define GCC_VERSION (__GNUC__ * 10000           \
                     + __GNUC_MINOR__ * 100     \
                     + __GNUC_PATCHLEVEL__)

// Note: Clang "fakes" GCC macros. So we actually want to detect the
// difference between the different implementations of the standard
// library. libstdc++ for GCC < 4.9 is bad. Clang is also bad if it is
// using the libstdc++ for GCC < 4.9. But clang is ok if it is using
// its own standard library (i.e., libc++). 

#if GCC_VERSION < 40900 && defined(__GLIBCXX__)
#define NO_ERASE_CONST_ITERATOR
#endif  // GCC_VERSION

#endif  // #if defined(__GNUC__) && ...


// ----------------------------------------------------------------------
// C++11 doesn't provide a std::make_unique() function. Therefore
// check for C++14 and if not C++14 then define our own make_unique()
// function.
// ----------------------------------------------------------------------

#if __cplusplus < 201402L

namespace support // a bit of a hack but might be justified in adding
                  // this to namespace std.
{
#include <memory>

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}
} // namespace support

#else

// alias support as an alias for std. Not necessary if we add
// make_unique to std namespace.
using support = std;

#endif // __cplusplus



#endif // SUPPORT_HPP
