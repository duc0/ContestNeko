#include "global.hpp"

#ifndef MATRIX_H
#define MATRIX_H

#define NO_WAY -1E9L

template<class T> class Matrix {
    vector<vector<T>> a;
    int nRow, nCol;

public:
    void init(int nRow, int nCol) {
        this->nRow = nRow;
        this->nCol = nCol;
        a.resize(nRow);
        for_inc(r, nRow) {
            a[r].resize(nCol);
            for_inc(c, nCol) {
                a[r][c] = 0;
            }
        }
    }

    void init(int nRow, int nCol, const vector<vector<T>> &val) {
        assert(val.size() == nRow);
        assert(val[0].size() == nCol);
        init(nRow, nCol);
        for_inc(r, nRow) {
            for_inc(c, nCol) {
                a[r][c] = val[r][c];
            }
        }
    }

    void init(const vector<vector<T>> &val) {
        init((int)val.size(), (int)val[0].size(), val);
    }

    Matrix& operator=(const vector<vector<T>> &val) {
        init(val);
        return *this;
    }

    Matrix operator + (const Matrix &o) const {
        assert(nRow == o.nRow);
        assert(nCol == o.nCol);
        Matrix ret;
        ret.init(nRow, nCol);
        for_inc(r, nRow) for_inc(c, nCol) ret.a[r][c] = a[r][c] + o.a[r][c];
        return ret;
    }

    Matrix operator * (const Matrix &o) const {
        assert(nCol == o.nRow);
        Matrix ret;
        ret.init(nRow, o.nCol);
        for_inc(r, nRow) {
            for_inc(c, nCol) {
                ret.a[r][c] = NO_WAY;
            }
        }
        for_inc(r, nRow) for_inc_range(c2, r, nCol - 1) for_inc_range(c, c2, o.nCol - 1) {
            ret.a[r][c] = max(ret.a[r][c], a[r][c2] + o.a[c2][c]);
        }
        return ret;
    }

    Matrix power(int k) const {
        assert(k >= 0);
        assert(nRow == nCol);
        if (k == 1) {
            Matrix ret(*this);
            return ret;
        } else if (k == 0) {
            Matrix ret;
            ret.init(nRow, nRow);
            for_inc(r, nRow) ret.a[r][r] = 1;
            return ret;
        } else if (k % 2 == 0) {
            Matrix tmp = power(k / 2);
            return tmp * tmp;
        } else {
            Matrix tmp = power(k - 1);
            return *this * tmp;
        }
    }

    vector<T>& operator[](int r) {
        return a[r];
    }

    friend std::ostream& operator<< (std::ostream& stream, const Matrix& matrix) {
        stream << "[matrix: row = " << matrix.nRow << ", col = " << matrix.nCol << endl;
        for_inc(r, matrix.nRow) {
            for_inc(c, matrix.nCol) {
                stream << matrix.a[r][c] << " ";
            }
            stream << endl;
        }
        stream << "]" << endl;
        return stream;
    }
};

#endif