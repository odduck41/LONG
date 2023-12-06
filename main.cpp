#include <iostream>
#include "LONG.h"


int main() {
    LONG a("1.1", 2);
    std::cout << a.to_10();
}
