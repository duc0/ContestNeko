#include "global.hpp"

#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

/*
 * Used to find min(x | predicate(x)), if predicate(x) is .. 0, 0, 0, 1, 1, 1, ...
 */
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

/*
 * Used to find max(x | predicate(x)), if predicate(x) is .. 1, 1, 1, 0, 0, 0, ...
 */
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

/*
 * Used to find max(x | predicate(x)), if predicate(x) is continuously .. 1, 1, 1, 0, 0, 0, ...
 */
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

/*
 * Used to find min(x | predicate(x)), if predicate(x) is continuously .. 0, 0, 0, 1, 1, 1, ...
 */
bool binarySearchMinReal(double minRange, double maxRange, double epsilon, const function<bool(double)> &predicate, double &result) {
    double l = minRange, r = maxRange, m, ret = maxRange + 1;
    while (r - l > epsilon) {
        m = l + (r - l) / 2;
        if (predicate(m)) {
            r = m;
            ret = m;
        } else {
            l = m;
        }
    }
    result = ret;
    return ret != maxRange + 1;
}

/*
 * Used to find the intersection of an increasing and a deceasing function
 */
bool binarySearchIntersection(double minRange, double maxRange, double epsilon, const function<double(double)> &increasing, const function<double(double)> &decreasing, double &intersection) {
    return binarySearchMinReal(minRange, maxRange, epsilon, [&](double x){
        //LOG(1, x << " " << increasing(x) << " " << decreasing(x));
        return increasing(x) >= decreasing(x);
    }, intersection);
}

#endif