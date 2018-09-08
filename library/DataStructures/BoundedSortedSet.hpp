#include "global.hpp"

#ifndef BSS_H
#define BSS_H

namespace cl {
/**
 * A sorted set with a maximum size. Elements beyond this boundary will be removed.
 * O(n) insert and O(1) access
 */
template<class V, int CAP>
class BoundedSortedSet {
  V back[CAP];
  int _size = 0;
 public:
  // O(n)
  void add(const V& v) {
    for (V& cur : back) {
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

  void addInOrder(const V& v) {
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

  const V& operator[](int index) const {
    assert(0 <= index && index < _size);
    return back[index];
  }
};

template<class T, int CAP>
BoundedSortedSet<T, CAP> merge(
    const BoundedSortedSet<T, CAP>& set1,
    const BoundedSortedSet<T, CAP>& set2) {
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
