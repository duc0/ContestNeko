#include "global.hpp"
#include "NDArray.hpp"
#include "Math.hpp"

#ifndef MATRIX_H
#define MATRIX_H

template<class T, class Calc = math::DefaultCalculator<T>>
class Matrix {
    cl::Array1<cl::Array1<T>> a;
    int nRow, nCol;
public:
    void init(int nRow, int nCol) {
        this->nRow = nRow;
        this->nCol = nCol;
        a.resize(nRow);
        FOR_INC_RANGE(r, 1, nRow) {
            a[r].resize(nCol);
            FOR_INC_RANGE(c, 1, nCol) {
                a[r][c] = Calc::zero();
            }
        }
    }

    void init(int nRow, int nCol, const cl::Array1<cl::Array1<T>> &val) {
        assert(val.size() == nRow);
        assert(val[1].size() == nCol);
        init(nRow, nCol);
        FOR_INC_RANGE(r, 1, nRow) {
            FOR_INC_RANGE(c, 1, nCol) {
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
        FOR_INC_RANGE(r, 1, nRow) FOR_INC_RANGE(c, 1, nCol) ret.a[r][c] = Calc::plus(a[r][c], o.a[r][c]);
        return ret;
    }

    Matrix operator*(const Matrix &o) const {
        assert(nCol == o.nRow);
        Matrix ret;
        ret.init(nRow, o.nCol);
        FOR_INC_RANGE(r, 1, nRow) FOR_INC_RANGE(c2, 1, nCol) if (a[r][c2] != Calc::zero())
                    FOR_INC_RANGE(c, 1, o.nCol) {
                        ret.a[r][c] = Calc::plus(ret.a[r][c], Calc::multiply(a[r][c2], o.a[c2][c]));
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
        FOR_INC_RANGE(r, 1, matrix.nRow) {
            FOR_INC_RANGE(c, 1, matrix.nCol) {
                stream << matrix.a[r][c] << " ";
            }
            stream << endl;
        }
        stream << "]" << endl;
        return stream;
    }
};

template<class T, class Calc = math::DefaultCalculator<T>>
class UpperTriMatrix {
    cl::Array1<cl::ArrayR<T>> a;
    int size;
public:
    void init(int size) {
        this->size = size;
        this->size = size;
        a.resize(size);
        FOR_INC_RANGE(r, 1, size) {
            a[r] = cl::ArrayR<T>(r, size);
            FOR_INC_RANGE(c, r, size) {
                a[r][c] = Calc::zero();
            }
        }
    }

    UpperTriMatrix operator+(const UpperTriMatrix &o) const {
        assert(size == o.size);
        UpperTriMatrix ret;
        ret.init(size);
        FOR_INC_RANGE(r, 1, size) FOR_INC_RANGE(c, r, size) ret.a[r][c] = Calc::plus(a[r][c], o.a[r][c]);
        return ret;
    }

    UpperTriMatrix operator*(const UpperTriMatrix &o) const {
        assert(size == o.size);
        UpperTriMatrix ret;
        ret.init(size);
        FOR_INC_RANGE(r, 1, size) FOR_INC_RANGE(c2, r, size) if (a[r][c2] != Calc::zero())
                    FOR_INC_RANGE(c, c2, size) {
                        ret.a[r][c] = Calc::plus(ret.a[r][c], Calc::multiply(a[r][c2], o.a[c2][c]));
                    }
        return ret;
    }

    UpperTriMatrix power(int k) const {
        return math::power(*this, k);
    }

    cl::ArrayR<T> &operator[](int r) {
        return a[r];
    }

    friend std::ostream &operator<<(std::ostream &stream, const UpperTriMatrix &matrix) {
        stream << "[UpperTriMatrix: size = " << matrix.size << endl;
        FOR_INC_RANGE(r, 1, matrix.size) {
            FOR_INC_RANGE(c, r, matrix.size) {
                stream << matrix.a[r][c] << " ";
            }
            stream << endl;
        }
        stream << "]" << endl;
        return stream;
    }
};

#endif