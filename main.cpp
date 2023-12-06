#include <iostream>
#include "LONG.h"


int main() {
    LONG a("1.1(01)", 2);
    LONG b("0.0(10)", 2);
    LONG c = a + b;
    std::cout << c;
}
