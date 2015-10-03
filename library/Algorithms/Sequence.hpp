#include "global.hpp"
#include "Iterator.hpp"

#ifndef SEQUENCE_H
#define SEQUENCE_H

/**
 * O(N)
 */
template <class T> void maximumSumContiguousSubsequence(const Iterable<T> &seq, T &result) {
    auto it = seq.iterator();
    bool has = false;
    T sum;
    while (it->hasNext()) {
        auto val = it->next();
        if (!has) {
            has = true;
            result = sum = val;
        } else {
            sum = ((sum > 0) ? sum : 0) + val;
            result = max(result, sum);
        }
    }
}

template <class T> void minimumSumContiguousSubsequence(const Iterable<T> &seq, T &result) {
    auto it = seq.iterator();
    bool has = false;
    T sum;
    while (it->hasNext()) {
        auto val = it->next();
        if (!has) {
            has = true;
            result = sum = val;
        } else {
            sum = ((sum < 0) ? sum : 0) + val;
            result = min(result, sum);
        }
    }
}

#endif
