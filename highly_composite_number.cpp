#include "highly_composite_number.hpp"

Integer PrimeExp::primePower(
    const std::size_t x,
    const unsigned long int y
) const {
    Integer ret = 1;
    const unsigned int p = static_cast<unsigned int>(prime(x));
    for(unsigned int i = 0; i < y; ++i) {
        ret *= p;
    }
    return ret;
}

PrimeExp::PrimeExp(const std::vector<unsigned int>& item, bool isKey) :
        _item(item), _isKey(isKey) {
    this->_numDivisor = 1;
    for(const unsigned int& e : this->_item) {
        this->_numDivisor *= e + 1;
    }
}

bool PrimeExp::operator>(const PrimeExp& object) const {
    Integer thisAdv = 1, objAdv = 1;
    std::vector<unsigned int> thisItem = this->_item;
    std::vector<unsigned int> objItem = object._item;
    const std::size_t thisSize = thisItem.size(), objSize = objItem.size();

    if(thisSize < objSize) {
        thisItem.resize(objSize);
    } else if(thisSize > objSize) {
        objItem.resize(thisSize);
    }
    const std::size_t size = thisItem.size();

    for(std::size_t i = 0; i < size; ++i) {
        const unsigned int t = thisItem[i], o = objItem[i];
        if(t < o) {
            objAdv *= this->primePower(i, o - t);
        } else if(thisItem[i] > objItem[i]) {
            thisAdv *= this->primePower(i, t - o);
        }
    }

    return thisAdv > objAdv;
}

std::vector<unsigned int> PrimeExp::getItem(void) const {
    return this->_item;
}

Integer PrimeExp::getNumber(void) const {
    Integer ret = 1;
    const std::size_t size = this->_item.size();
    for(std::size_t i = 0; i < size; ++i) {
        ret *= this->primePower(i, this->_item[i]);
    }
    return ret;
}

Integer PrimeExp::getNumDivisor(void) const {
    return this->_numDivisor;
}

bool PrimeExp::isKey(void) const {
    return this->_isKey;
}

std::vector<Integer> PrimeExp::getDivisor(void) {
    if(this->_divisor.size() > 0) return this->_divisor;

    std::vector<Integer> ret{1};
    const std::size_t size = this->_item.size();
    for(std::size_t i = 0; i < size; ++i) {
        const std::vector<Integer> tmp = std::move(ret);
        const unsigned int max = this->_item[i] + 1;
        ret.clear();
        ret.reserve(tmp.size() * max);
        for(unsigned int j = 0; j < max; ++j) {
            const Integer t = this->primePower(i, j);
            for(const Integer& e : tmp) {
                ret.push_back(e * t);
            }
        }
    }

    std::sort(ret.begin(), ret.end());
    this->_divisor = ret;
    return ret;
}

unsigned int HighlyCompositeNumber::computeThreshold(
    const int x,
    const int y
) const {
    int ret = 1;
    for(int t = y; x >= y * t; t *= y, ++ret);
    return static_cast<unsigned int>(ret);
}

void HighlyCompositeNumber::insert(const std::size_t size) {
    std::vector<unsigned int> min(size), max(size), item(size);
    std::vector<int> p(size + 1);
    for(std::size_t i = 0; i <= size; ++i) {
        p[i] = prime(i);
    }
    const int back = p[size - 1], end = p[size];
    for(std::size_t i = 0; i < size; ++i) {
        const int t = p[i];
        item[i] = min[i] = this->computeThreshold(back, t);
        max[i] = 2 * this->computeThreshold(end, t);
    }
    if(size > 2) {
        max[size - 1] = 1;
    }

    while(true) {
        std::size_t index = 0;
        while(index < size) {
            ++item[index];
            if(item[index] <= max[index]) break;
            ++index;
        }
        if(index >= size) break;
        for(std::size_t i = 0; i < index; ++i) {
            item[i] = std::max(item[index], min[i]);
        }
        this->_queue.emplace(item, false);
    }
    item.resize(size + 1);
    for(std::size_t i = 0; i <= size; ++i) {
        item[i] = this->computeThreshold(end, p[i]);
        if(item[i] > 1) continue;
        for(++i ; i <= size; ++i) {
            item[i] = 1;
        }
    }
    this->_queue.emplace(std::move(item), true);
}

HighlyCompositeNumber::HighlyCompositeNumber() : _record(0) {
    this->insert(1);
    this->_init = 0;
}

Integer HighlyCompositeNumber::next(void) {
    if(this->_init < 2) {
        ++this->_init;
        return this->_init;
    }

    while(true) {
        const PrimeExp ret = std::move(this->_queue.top());
        this->_queue.pop();
        if(ret.isKey()) {
            this->insert(ret.getItem().size());
        }
        const Integer numDivisor = ret.getNumDivisor();
        if(numDivisor > this->_record) {
            this->_record = numDivisor;
            return ret.getNumber();
        }
    }
}
