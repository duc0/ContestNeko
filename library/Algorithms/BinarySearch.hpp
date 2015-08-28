#include "global.hpp"

template<class T> bool binarySearchMin(const T &minIndex, const T &maxIndex, const function<bool(T)> &predicate, T &result) {
    T leftIndex = minIndex, rightIndex = maxIndex, midIndex, ret = maxIndex + 1;
    while (leftIndex <= rightIndex) {
        midIndex = leftIndex + (rightIndex - leftIndex) / 2;
        if (predicate(midIndex)) {
            ret = midIndex;
            rightIndex = midIndex - 1;
        } else {
            leftIndex = midIndex + 1;
        }
    }
    result = ret;
    return ret != maxIndex + 1;
}

template<class T> bool binarySearchMax(const T &minIndex, const T &maxIndex, const function<bool(T)> &predicate, T &result) {
    T leftIndex = minIndex, rightIndex = maxIndex, midIndex, ret = minIndex - 1;
    while (leftIndex <= rightIndex) {
        midIndex = leftIndex + (rightIndex - leftIndex) / 2;
        if (predicate(midIndex)) {
            ret = midIndex;
            leftIndex = midIndex + 1;
        } else {
            rightIndex = midIndex - 1;
        }
    }
    result = ret;
    return ret != minIndex - 1;
}

bool binarySearchMaxReal(double minRange, double maxRange, double epsilon, const function<bool(double)> &predicate, double &result) {
    double l = minRange, r = maxRange, m, ret = minRange - 1;
    while (r - l > epsilon) {
        m = l + (r - l) / 2;
        if (predicate(m)) {
            ret = m;
            l = m;
        } else {
            r = m;
        }
    }
    result = ret;
    return ret != minRange - 1;
}

bool binarySearchMinReal(double minRange, double maxRange, double epsilon, const function<bool(double)> &predicate, double &result) {
    double l = minRange, r = maxRange, m, ret = maxRange + 1;
    while (r - l > epsilon) {
        m = l + (r - l) / 2;
        if (predicate(m)) {
            l = m;
            ret = m;
        } else {
            r = m;
        }
    }
    result = ret;
    return ret != maxRange + 1;
}