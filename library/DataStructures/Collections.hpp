#include "global.hpp"

#ifndef COLLECTIONS_H
#define COLLECTIONS_H

namespace cl {
    template<class K, class V> class Map {
        std::map<K, V> map;

        typedef typename std::map<K, V>::iterator iterator;
        typedef typename std::map<K, V>::reverse_iterator reverse_iterator;
    public:
        bool empty() {
            return map.empty();
        }

        iterator begin() {
            return map.begin();
        }

        iterator end() {
            return map.end();
        }

        reverse_iterator rbegin() {
            return map.rbegin();
        }

        reverse_iterator rend() {
            return map.rend();
        }

        K firstKey() {
            assert(!empty());
            return begin()->first;
        }

        V firstValue() {
            assert(!empty());
            return begin()->second;
        }

        K lastKey() {
            assert(!empty());
            return map.rbegin()->first;
        }

        V lastValue() {
            assert(!empty());
            return map.rbegin()->second;
        }

        void removeLast() {
            map.erase(lastKey());
        }

        void removeFirst() {
            map.erase(firstKey());
        }

        V& operator[] (const K& k) {
            return map[k];
        }
    };

    template<class V> class Array {
        std::vector<V> vec;

        typedef typename std::vector<V>::iterator iterator;
        typedef typename std::vector<V>::const_iterator const_iterator;

    public:
        Array() {}
        Array(int sz) : vec(vector<V>(sz)) {}

        void resize(int sz) {
            vec.resize(sz);
        }

        void assertIndex(int index) const {
            ASSERT(index >= 0 && index < vec.size(), "Index of out bounds, size = " << size() << ", index = " << index);
        }

        V& operator[] (int index) {
            assertIndex(index);
            return vec[index];
        }

        const V& operator[] (int index) const {
            assertIndex(index);
            return vec[index];
        }

        /**
         * Return the new index
         */
        int add(const V &v) {
            vec.push_back(v);
            return vec.size() - 1;
        }

        iterator begin() {
            return vec.begin();
        }

        const_iterator begin() const {
            return vec.begin();
        }

        iterator end() {
            return vec.end();
        }

        const_iterator end() const {
            return vec.end();
        }

        int size() const {
            return vec.size();
        }

        V& last() {
            return this[size() - 1];
        }

        V& first() {
            return this[0];
        }

        bool empty() {
            return size() == 0;
        }

        friend std::ostream &operator<<(std::ostream &stream, const Array<V> &array) {
            bool first = true;
            stream << "Array of " << array.size() << ": [";
            for (auto &v : array) {
                if (!first) {
                    stream << ", ";
                }
                first = false;
                stream << v;
            }
            stream << "]";
            return stream;
        }
    };

    /**
     * 1 based array
     */
    template<class V> class Array1 : public Array<V> {
    public:
        Array1() {}
        Array1(int sz) : Array<V>(sz) {}

        V& operator[] (int index) {
            return Array<V>::operator[](index - 1);
        }

        const V& operator[] (int index) const {
            return Array<V>::operator[](index - 1);
        }
    };

    /**
     * Range based array
     */
    template<class V> class ArrayR : public Array<V> {
        int minIndex, maxIndex;
    public:
        ArrayR() {}
        ArrayR(int minIndex, int maxIndex) : Array<V>(maxIndex - minIndex + 1), minIndex(minIndex), maxIndex(maxIndex) {
            assert(minIndex <= maxIndex);
            assert(Array<V>::size() == (maxIndex - minIndex + 1));
        }

        V& operator[] (int index) {
            return Array<V>::operator[](index - minIndex);
        }

        const V& operator[] (int index) const {
            return Array<V>::operator[](index - minIndex);
        }
    };
}

#endif
