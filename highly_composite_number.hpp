#ifndef HIGHLY_COMPOSITE_NUMBER
#define HIGHLY_COMPOSITE_NUMBER

#include "prime.hpp"
#include <algorithm>
#include <queue>

using Integer = unsigned long long int;

class PrimeExp {
    std::vector<unsigned int> _item;
    std::vector<Integer> _divisor;
    Integer _numDivisor;
    bool _isKey;

    Integer primePower(std::size_t, unsigned long int) const;

public:
    PrimeExp(const std::vector<unsigned int>&, bool);
    PrimeExp(const PrimeExp&) = default;
    PrimeExp& operator=(const PrimeExp&) = default;
    PrimeExp& operator=(PrimeExp&&) noexcept = default;

    bool operator>(const PrimeExp&) const;

    std::vector<unsigned int> getItem(void) const;
    Integer getNumber(void) const;
    Integer getNumDivisor(void) const;
    bool isKey(void) const;
    std::vector<Integer> getDivisor(void);
};

class HighlyCompositeNumber {
    Integer _init;
    Integer _record;
    std::priority_queue<
        PrimeExp,
        std::vector<PrimeExp>,
        std::greater<PrimeExp>
    > _queue;

    unsigned int computeThreshold(const int, const int) const;
    void insert(const std::size_t);

public:
    HighlyCompositeNumber();

    Integer next(void);
};

#endif // HIGHLY_COMPOSITE_NUMBER
