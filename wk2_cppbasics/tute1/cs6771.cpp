namespace cs6771
{


// Alternatives:
// void order3(int *const a, int *const b, int *const c) // OK
// void order3(const int *a, const int *b, const int *c) // ERROR
// a pointer to a const int - means we can't modify its value!!!!

void order3(int *a, int *b, int *c)
{
    if (*a < *c) {
        int t = *a;
        *a = *c;
        *c = t;
    }
    if (*a < *b) {
        int t = *a;
        *a = *b;
        *b = t;
    }
    if (*b < *c) {
        int t = *b;
        *b = *c;
        *c = t;
    }
}

// Alternative:
// void order3(const unsigned int &a, const unsigned int &b, const unsigned int &c) // ERROR

void order3(unsigned int& a, unsigned int& b, unsigned int& c)
{
    if (a > c) {
        int t = a;
        a = c;
        c = t;
    }
    if (b > c) {
        int t = b;
        b = c;
        c = t;
    }
    if (a > b) {
        int t = a;
        a = b;
        b = t;
    }
}

} // namespace cs6771
