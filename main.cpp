#include <iostream>
#include "LONG.h"

using namespace std;

int main() {
    LONG a = "-115.167(900)"; //
    LONG b = "-115.167(901)"; //
    cout << (b == a);
}
