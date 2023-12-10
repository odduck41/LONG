#include <iostream>
#include "LONG.h"

using namespace std;

int main() {
    std::string e = "3242135123";
    LONG a = e.c_str();
    cout << a;
}
