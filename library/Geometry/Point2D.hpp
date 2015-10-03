#include "global.hpp"

#ifndef POINT2D_H
#define POINT2D_H

template <class T> struct Point2D {
    T x, y;
    bool operator<(const Point2D &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
    bool operator==(const Point2D &p) const { return x == p.x && y == p.y; }
    Point2D operator+(const Point2D &p) const {
        return Point2D{x + p.x, y + p.y};
    }
    Point2D operator-(const Point2D &p) const {
        return Point2D{x - p.x, y - p.y};
    }
    T dotProduct(const Point2D &p) const { return x * p.x + y * p.y; }
    T crossProduct(const Point2D &p) const { return x * p.y - y * p.x; }
    T distance(const Point2D &p) const {
        return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
    }
    friend std::ostream &operator<<(std::ostream &stream, const Point2D<T> &p) {
        stream << "Point (" << p.x << ", " << p.y << ")";
        return stream;
    }
};
template <class T>
T cross(const Point2D<T> &o, const Point2D<T> &a, const Point2D<T> &b) {
    return (a - o).crossProduct(b - o);
}
template <class T> Point2D<T> makePoint(T x, T y) { return Point2D<T>{x, y}; }
namespace std {
    template <class T> struct hash<Point2D<T>> {
        size_t operator()(const Point2D<T> &k) const {
            return (hash<T>()(k.x) ^ hash<T>()(k.y));
        }
    };
}

#endif