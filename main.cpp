#include <iostream>
#include "LONG.h"
#include <sstream>


int main() {
    std::string first;
    int second;
    std::cin >> first >> second;
    LONG a(first);
    std::cout << (a ^ second);
}
