#include <iostream>

template <typename FUNCTION> inline void loop(int n, FUNCTION f) {
    for (int i = 0; i < n; ++i) { f(i); }
}
int main(void) {
    loop(5, [](int jj) { std::cout << "This is iteration #" << jj << std::endl; });
}