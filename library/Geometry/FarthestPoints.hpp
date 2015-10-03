#include "global.hpp"
#include "Point.hpp"
#include "ConvexHull.hpp"

#ifndef FARTHEST_POINTS_H
#define FARTHEST_POINTS_H

// Usage: construct the algorithm with a set of 2D points
// And then get the farthest two points
// O(nlogn)

template <class T> class FarthestTwoPoints {
    T dist;

public:
    FarthestTwoPoints(const vector<Point2D<T>> &p) {
        assert(p.size() >= 2);
        ConvexHull<T> ch(p);
        const vector<Point2D<T>> &u = ch.getUpperHull();
        const vector<Point2D<T>> &l = ch.getLowerHull();
        int i = 0, j, m;
        j = (int)u.size() - 1;
        m = (int)l.size() - 1;
        dist = numeric_limits<T>::min();
        while (i < m || j > 0) {
            T d = u[i].distance(l[j]);
            if (d > dist) {
                dist = d;
            }
            if (i == m)
                j--;
            else if (j == 0)
                i++;
            else {
                if ((l[j] - l[j - 1]).crossProduct(u[i + 1] - u[i]) > 0)
                    i++;
                else
                    j--;
            }
        }
    }

    T getFarthestDistance() { return dist; }
};

#endif