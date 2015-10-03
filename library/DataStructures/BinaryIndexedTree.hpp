#include "global.hpp"

#ifndef BIT_H
#define BIT_H

template <class T> class BinaryIndexedTree {
    vector<T> val;
    int n, minIndex, maxIndex;

public:
    BinaryIndexedTree() {}

    BinaryIndexedTree(int n): BinaryIndexedTree(1, n) {}

    BinaryIndexedTree(int minIndex, int maxIndex) {
        init(minIndex, maxIndex);
    }

    void init(int minIndex, int maxIndex) {
        this->minIndex = minIndex;
        this->maxIndex = maxIndex;
        this->n = maxIndex - minIndex + 1;
        val.resize(n + 1);
    }

    void add(int i, int v) {
        i = i - minIndex + 1;
        for (; i <= n; i += i & -i) {
            val[i] += v;
        }
    }
    T sum(int i) {
        i = i - minIndex + 1;
        if (i <= 0) return 0;
        if (i > n) i = n;
        T s = 0;
        for (; i > 0; i -= i & -i)
            s += val[i];
        return s;
    }

    T sum(int i1, int i2) { return sum(i2) - sum(i1 - 1); }
};

template <class T> class BinaryIndexedTree3D {
    vector<vector<vector<T>>> val;
    int n, minIndex, maxIndex;

public:
    BinaryIndexedTree3D(int n): BinaryIndexedTree3D(1, n) {}

    BinaryIndexedTree3D(int minIndex, int maxIndex) {
        this->minIndex = minIndex;
        this->maxIndex = maxIndex;
        this->n = maxIndex - minIndex + 1;
        val.resize(n + 1);
        for_inc_range(i, 1, n) {
            val[i].resize(n + 1);
            for_inc_range(j, 1, n) {
                val[i][j].resize(n + 1);
            }
        }
    }

    void add(int x0, int y0, int z0, int v) {
        x0 = x0 - minIndex + 1;
        y0 = y0 - minIndex + 1;
        z0 = z0 - minIndex + 1;
        for (int x = x0; x <= n; x += x & -x) for (int y = y0; y <= n; y += y & - y) for (int z = z0; z <= n; z += z & -z) {
                    val[x][y][z] += v;
                }
    }

    T sum(int x0, int y0, int z0) {
        x0 = x0 - minIndex + 1;
        y0 = y0 - minIndex + 1;
        z0 = z0 - minIndex + 1;
        if (x0 <= 0 || y0 <= 0 || z0 <= 0) return 0;
        if (x0 > n) x0 = n;
        if (y0 > n) y0 = n;
        if (z0 > n) z0 = n;
        T s = 0;
        for (int x = x0; x > 0; x -= x & -x) for (int y = y0; y > 0; y -= y & -y) for (int z = z0; z > 0; z -= z & -z)
                    s += val[x][y][z];
        return s;
    }

    T sum(int x1, int y1, int z1, int x2, int y2, int z2) {
        return sum(x2, y2, z2) - sum(x1 - 1, y2, z2) - sum(x2, y1 - 1, z2) - sum(x2, y2, z1 - 1)
               + sum(x1 - 1, y1 - 1, z2) + sum(x2, y1 - 1, z1 - 1) + sum(x1 - 1, y2, z1 - 1) - sum(x1 - 1, y1 - 1, z1 - 1);
    }
};

#endif