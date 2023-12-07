#include <iostream>
#include "LONG.h"


int main() {
    LONG a("0.1", 10);
    LONG b("10", 10);
    std::cout << (a*b);
}
