#include <iostream>
#include "LONG.h"


int main() {
    LONG a("5.67(90)");
    LONG b("6.0(62)");
    LONG c = a + b;
    std::cout << c;
}
