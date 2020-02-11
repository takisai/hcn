#include "prime.hpp"

int prime(std::size_t index) {
    static std::vector<int> p{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
    if(index < p.size()) return p[index];

    std::size_t i = p.size(), j;
    p.resize(index + 1);
    int target = p[i - 1] + 2;
    while(i <= index) {
        for(j = 0; j < i; ++j) {
            if(target % p[j] == 0) break;
        }
        if(j == i) {
            p[i] = target;
            ++i;
        }
        target += 2;
    }
    return p[index];
}
