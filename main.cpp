#include <iostream>
#include "LONG.h"


int main() {
    std::string first;
    std::string second;
    std::cin >> first >> second;
    LONG a(first);
    LONG b(second);
    std::cout << (a / b);
}
