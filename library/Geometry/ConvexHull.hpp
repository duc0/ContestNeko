#include "global.hpp"
#include "Point.hpp"

#ifndef CONVEXHULL_H
#define CONVEXHULL_H

// O(nlogn)
template <class T> class ConvexHull {
    vector<Point2D<T>> upper;
    vector<Point2D<T>> lower;

public:
    ConvexHull(const vector<Point2D<T>> &points) {
        vector<Point2D<T>> p = points;
        int j = 0, k = 0, n = (int)p.size();
        sort(p.begin(), p.end());
        upper.resize(2 * n);
        lower.resize(2 * n);
        for_inc(i, n) {
            while (j >= 2 && cross(lower[j - 2], lower[j - 1], p[i]) <= 0)
                j--;
            while (k >= 2 && cross(upper[k - 2], upper[k - 1], p[i]) >= 0)
                k--;
            lower[j++] = p[i];
            upper[k++] = p[i];
        }
        upper.resize(k);
        lower.resize(j);
    }

    const vector<Point2D<T>> &getUpperHull() const { return upper; }

    const vector<Point2D<T>> &getLowerHull() const { return lower; }
};

#endif