#include "highly_composite_number.hpp"
#include <iostream>

int main(void) {
    HighlyCompositeNumber hcn;

    for(int i = 1; i <= 170; ++i) {
        std::cout << i << " " << hcn.next() << std::endl;
    }
    return 0;
}
