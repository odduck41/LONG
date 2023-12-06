#include <iostream>
#include "LONG.h"
#include <sstream>


int main() {
    std::string first, second;
    std::cin >> first >> second;
    LONG a(first, 10);
    LONG b(second, 10);
    LONG c = a * b;
    std::istringstream i(first);
    std::istringstream j(second);
    int ae, be;
    i >> ae;
    j >> be;
    int ce = ae * be;
    std::cout << c << " " << ce;
}
