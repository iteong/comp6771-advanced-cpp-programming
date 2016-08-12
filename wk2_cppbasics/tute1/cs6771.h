/*
 * NOTE: using the ifndef trick to make sure the header is only
 * included once. You could also use "#pragma once". "#pragma once" is
 * technically compiler specific (and not part of the C++ standard)
 * but most compilers support it.
 *
 */

#ifndef CS6771_H
#define CS6771_H

namespace cs6771
{

void order3(int *a, int *b, int *c);
void order3(unsigned int& a, unsigned int& b, unsigned int& c);



// Alternative prototypes to test:
//void order3(int *const a, int *const b, int *const c); // OK
//void order3(const int *a, const int *b, const int *c); // ERROR

// Note: the following have the same meaning
// void order3(const int *a, const int *b, const int *c)
// void order3(int const *a, int const *b, int const *c)

//void order3(const unsigned int &a, const unsigned int &b, const unsigned int &c); // ERROR

// Note again: the following have the same meaning
//void order3(const unsigned int &a, const unsigned int &b, const unsigned int &c);
//void order3(unsigned int const &a, unsigned int const &b, unsigned int const &c);


} // namespace cs6771


#endif // CS6771_H


