// week11.cpp e.g. 4
// Callum Howard, 2016

#include<iostream>
#include<typeinfo>

// 1st one const-version will be called, as f() has rvalue-reference, which acts as a const
void e(const int &i, int j, int k) {
  std::cout << "1 ";
}

void e(int &i, int j, int k) {
  std::cout << "2 ";
}

template <typename A, typename B, typename C>
void f(A &&a, B &&b, C &&c) {
  using std::forward;
  e(forward<A>(a), forward<B>(b), forward<C>(c));
}

int k{1};
int g() { return k; }

int main() {
  f(1,2,3);
  int i{1};
  f(i,2,3);
  const int &j = i;
  f(j,2,3);
  f(g(),2,3);
}