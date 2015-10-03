#include "global.hpp"

#ifndef POINT2D_H
#define POINT2D_H

namespace geometry {
    double EPSILON = 1E-6;

    template<class T>
    struct Point2D {
        T x, y;

        Point2D() {}

        Point2D(T x, T y) : x(x), y(y) {}

        bool operator<(const Point2D &p) const {
            return x < p.x || (x == p.x && y < p.y);
        }

        bool operator==(const Point2D &p) const { return x == p.x && y == p.y; }

        T distance(const Point2D &p) const {
            return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
        }

        friend std::ostream &operator<<(std::ostream &stream, const Point2D<T> &p) {
            stream << "Point (" << p.x << ", " << p.y << ")";
            return stream;
        }

        static Point2D<T> of(T x, T y) {
            return Point2D<T>{x, y};
        }
    };

    template <class T> struct Vec2D : Point2D<T> {
        Vec2D() {}

        Vec2D(T x, T y) : x(x), y(y) {}

        Vec2D(const Point2D<T> &a, const Point2D<T> &b) : x(b.x - a.x), y(b.y - a.y) {}

        Vec2D operator+(const Vec2D &p) const {
            return Vec2D(x + p.x, y + p.y);
        }

        Vec2D operator-(const Vec2D &p) const {
            return Vec2D(x - p.x, y - p.y);
        }

        T dot(const Vec2D &p) const { return x * p.x + y * p.y; }

        T cross(const Vec2D &p) const { return x * p.y - y * p.x; }

        friend std::ostream &operator<<(std::ostream &stream, const Point2D<T> &p) {
            stream << "Vector (" << p.x << ", " << p.y << ")";
            return stream;
        }
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
    T cross(const Point2D<T> &o, const Point2D<T> &a, const Point2D<T> &b) {
        return Vec2D(o, a).cross(Vec2D(o, b));
    }

    template<class T> bool collinear(const Point2D<T> &o, const Point2D<T> &a, const Point2D<T> &b) {
        return isEqual(cross(o, a, b), 0);
    }

    // A turn right to B, with the origin O
    template<class T> bool rightTurn(const Point2D<T> &o, const Point2D<T> &a, const Point2D<T> &b) {
        return isGreater(cross(o, a, b), 0);
    }

    // A turn left to B, with the origin O
    template<class T> bool leftTurn(const Point2D<T> &o, const Point2D<T> &a, const Point2D<T> &b) {
        return isSmaller(cross(o, a, b), 0);
    }
}

namespace std {
    template <class T> struct hash<geometry::Point2D<T>> {
        size_t operator()(const geometry::Point2D<T> &k) const {
            return (hash<T>()(k.x) ^ hash<T>()(k.y));
        }
    };
}

#endif