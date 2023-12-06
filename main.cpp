#include <iostream>
#include "LONG.h"


int main() {
    LONG a("5.(90)");
    LONG b("6.0(1)");
    LONG c = a + b;
    std::cout << c;
}
