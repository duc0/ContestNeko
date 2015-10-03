#include "global.hpp"
#include "Collections.hpp"
#include "Math.hpp"

#ifndef MATRIX_H
#define MATRIX_H

#define NO_WAY -1E9L

template <class T> T zero() {
    return 0;
}

template<class T>
class Matrix {
    cl::Array1<cl::Array1<T>> a;
    int nRow, nCol;

public:
    void init(int nRow, int nCol) {
        this->nRow = nRow;
        this->nCol = nCol;
        a.resize(nRow);
        for_inc_range(r, 1, nRow) {
            a[r].resize(nCol);
            for_inc_range(c, 1, nCol) {
                a[r][c] = zero<T>();
            }
        }
    }

    void init(int nRow, int nCol, const cl::Array1<cl::Array1<T>> &val) {
        assert(val.size() == nRow);
        assert(val[1].size() == nCol);
        init(nRow, nCol);
        for_inc_range(r, 1, nRow) {
            for_inc_range(c, 1, nCol) {
                a[r][c] = val[r][c];
            }
        }
    }

    void init(const cl::Array1<cl::Array1<T>> &val) {
        init(val.size(), val[1].size(), val);
    }

    Matrix &operator=(const cl::Array1<cl::Array1<T>> &val) {
        init(val);
        return *this;
    }

    Matrix operator+(const Matrix &o) const {
        assert(nRow == o.nRow);
        assert(nCol == o.nCol);
        Matrix ret;
        ret.init(nRow, nCol);
        for_inc_range(r, 1, nRow) for_inc_range(c, 1, nCol) ret.a[r][c] = a[r][c] + o.a[r][c];
        return ret;
    }

    Matrix operator*(const Matrix &o) const {
        assert(nCol == o.nRow);
        Matrix ret;
        ret.init(nRow, o.nCol);
        for_inc_range(r, 1, nRow) for_inc_range(c2, 1, nCol) if (a[r][c2] != zero<T>())
                    for_inc_range(c, 1, o.nCol) {
                        ret.a[r][c] = ret.a[r][c] + a[r][c2] * o.a[c2][c];
                    }
        return ret;
    }

    Matrix power(int k) const {
        return math::power(*this, k);
    }

    cl::Array1<T> &operator[](int r) {
        return a[r];
    }

    friend std::ostream &operator<<(std::ostream &stream, const Matrix &matrix) {
        stream << "[matrix: row = " << matrix.nRow << ", col = " << matrix.nCol << endl;
        for_inc_range(r, 1, matrix.nRow) {
            for_inc_range(c, 1, matrix.nCol) {
                stream << matrix.a[r][c] << " ";
            }
            stream << endl;
        }
        stream << "]" << endl;
        return stream;
    }
};

#endif