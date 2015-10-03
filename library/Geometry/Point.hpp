#include "global.hpp"

#ifndef POINT2D_H
#define POINT2D_H

namespace geometry2D {
    double EPSILON = 1E-6;

    template<class T> struct Point {
        T x, y;

        Point() {}

        Point(T x, T y) : x(x), y(y) {}

        bool operator==(const Point &p) const { return isEqual(x, p.x) && isEqual(y, p.y); }

        T distance(const Point &p) const {
            return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
        }

        friend std::ostream &operator<<(std::ostream &stream, const Point<T> &p) {
            stream << "Point (" << p.x << ", " << p.y << ")";
            return stream;
        }

        static Point<T> of(T x, T y) {
            return Point<T>{x, y};
        }
    };

    template <class T> struct Vec : Point<T> {
        Vec() {}

        Vec(T x, T y) : x(x), y(y) {}

        Vec(const Point<T> &a, const Point<T> &b) : x(b.x - a.x), y(b.y - a.y) {}

        Vec operator+(const Vec &p) const {
            return Vec(x + p.x, y + p.y);
        }

        Vec operator-(const Vec &p) const {
            return Vec(x - p.x, y - p.y);
        }

        T normSqr() {
            return x * x + y * y;
        }

        T norm() {
            return sqrt(normSqr());
        }

        T dot(const Vec &p) const { return x * p.x + y * p.y; }

        T cross(const Vec &p) const { return x * p.y - y * p.x; }

        friend std::ostream &operator<<(std::ostream &stream, const Point<T> &p) {
            stream << "Vector (" << p.x << ", " << p.y << ")";
            return stream;
        }
    };

    template <class T> struct Line {
        // ax + by = c
        T a, b, c;

        Line() {}

        Line(T a, T b, T c)  {
            assert(!isEqual(a, 0) && !isEqual(b, 0) && "a and b cannot be both 0");
            T norm = Vec(a, b).norm();
            this->a = a / norm;
            this->b = b / norm;
            this->c = c / norm;
        }

        bool operator==(const Line &other) const {
            return isEqual(a, other.a) && isEqual(b, other.b) && isEqual(c, other.c);
        }

        Line(const Point<T> &p1, const Point<T> &p2) {

        }
    };

    // Line Segment
    template <class T> struct Seg {
        Point p1, p2;

        Seg() {}

        Seg(const Point &p1, const Point &p2) : p1(p1), p2(p2) {}
    };

    void setEpsilon(double eps) {
        EPSILON = eps;
    }

    template<class T> bool isEqual(T val1, T val2) {
        return val1 == val2;
    }

    template<class T> bool isGreater(T val1, T val2) {
        return val1 > val2;
    }

    template<class T> bool isSmaller(T val1, T val2) {
        return val1 < val2;
    }

    template<> bool isEqual(double val1, double val2) {
        return fabs(val1 - val2) < EPSILON;
    }

    template<> bool isGreater(double val1, double val2) {
        return val1 - val2 > EPSILON;
    }

    template<> bool isSmaller(double val1, double val2) {
        return val1 - val2 < -EPSILON;
    }

    template<class T>
    T cross(const Point<T> &o, const Point<T> &a, const Point<T> &b) {
        return Vec(o, a).cross(Vec(o, b));
    }

    template<class T> bool collinear(const Point<T> &o, const Point<T> &a, const Point<T> &b) {
        return isEqual(cross(o, a, b), 0);
    }

    // A turn right to B, with the origin O
    template<class T> bool rightTurn(const Point<T> &o, const Point<T> &a, const Point<T> &b) {
        return isGreater(cross(o, a, b), 0);
    }

    // A turn left to B, with the origin O
    template<class T> bool leftTurn(const Point<T> &o, const Point<T> &a, const Point<T> &b) {
        return isSmaller(cross(o, a, b), 0);
    }
}

namespace std {
    template <class T> struct hash<geometry2D::Point<T>> {
        size_t operator()(const geometry2D::Point<T> &k) const {
            return (hash<T>()(k.x) ^ hash<T>()(k.y));
        }
    };
}

#endif