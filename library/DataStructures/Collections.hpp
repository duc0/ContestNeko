#include "global.hpp"

#ifndef COLLECTIONS_H
#define COLLECTIONS_H

namespace cl {
    template<class V> class NDArray {
     public:
      NDArray(const initializer_list<int>& shape, const V& initialValue,
          int defaultStartingPos = 0) : shape_(shape) {
        a_.resize(getSize());
        REPEAT(getDimension()) {
          startingPos_.push_back(defaultStartingPos);
        }
        fillValue(initialValue);
      }

      void setStartingPos(const initializer_list<int>& startingPos) {
        assert(startingPos.size() == getDimension());
        startingPos_ = startingPos;
      }

      int getSize() const {
        int size = 1;
        for (auto x : shape_) {
          size *= x;
        }
        return size;
      }

      int dim(int i) const {
        return shape_[i];
      }

      int getDimension() const {
        return shape_.size();
      }

      void fillValue(const V& value) {
        FOR_INC(i, a_.size()) {
          a_[i] = value;
        }
      }

      const V& operator[] (int i0) const {
        return operator()(i0);
      }

      const V& operator() (int i0) const {
        assert(getDimension() == 1);
        return get(i0 - startingPos_[0]);
      }

      V& operator() (int i0) {
        assert(getDimension() == 1);
        return get(i0 - startingPos_[0]);
      }

      V& operator() (int i0, int i1) {
        assert(getDimension() == 2);
        return get((i0 - startingPos_[0]) * dim(1) + (i1 - startingPos_[1]));
      }

     private:
      vector<V> a_;
      vector<int> shape_;
      vector<int> startingPos_;

      V& get(int index) {
        assert(0 <= index && index < a_.size());
        return a_[index];
      }

      const V& get(int index) const {
        assert(0 <= index && index < a_.size());
        return a_[index];
      }
    };

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

    /**
     * A sorted set with a maximum size. Elements beyond this boundary will be removed.
     * O(n) insert and O(1) access
     */
    template<class V, int CAP> class BoundedSortedSet {
        V back[CAP];
        int _size = 0;
    public:
        // O(n)
        void add(const V &v) {
            for (V &cur : back) {
                if (cur == v) {
                    return;
                }
            }
            if (_size == CAP && v > back[_size - 1]) {
                return;
            }
            if (_size < CAP) {
                _size++;
            }
            int i = _size - 1;
            while (i > 0 && back[i - 1] > v) {
                back[i] = back[i - 1];
                i--;
            }
            back[i] = v;
        }

        void addInOrder(const V &v) {
            if (_size > 0 && back[_size - 1] == v) {
                return;
            }
            assert(_size == 0 || back[_size - 1] < v);
            back[_size] = v;
            _size++;
        }

        int size() const {
            return _size;
        }

        const V& operator[] (int index) const {
            assert(0 <= index && index < _size);
            return back[index];
        }
    };

    template <class T, int CAP> BoundedSortedSet<T, CAP> merge(const BoundedSortedSet<T, CAP> &set1, const BoundedSortedSet<T, CAP> &set2) {
        BoundedSortedSet<T, CAP> result;
        for (int i1 = 0, i2 = 0; (i1 < set1.size() || i2 < set2.size());) {
            bool use1 = i2 >= set2.size() || (i1 < set1.size() && set1[i1] < set2[i2]);
            if (use1) {
                result.addInOrder(set1[i1++]);
            } else {
                result.addInOrder(set2[i2++]);
            }
            if (result.size() >= CAP) {
                break;
            }
        }
        return result;
    }
}

#endif
