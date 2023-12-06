#include <iostream>
#include "LONG.h"


int main() {
    LONG a("6.0(1)", 10);
    LONG b(" 5", 10);
    LONG c = a + b;
    std::cout << c;
}
