#include "global.hpp"

#ifndef NDARRAY_H
#define NDARRAY_H

namespace cl {
template<class V>
class NDArray {
 public:
  NDArray(
      const initializer_list<int>& shape, const V& initialValue,
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

  int startingPos(int i) const {
    return startingPos_[i];
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

  const V& operator[](int i0) const {
    return operator()(i0);
  }

  const V& operator()(int i0) const {
    assert(getDimension() == 1);
    return get(i0 - startingPos_[0]);
  }

  V& operator()(int i0) {
    assert(getDimension() == 1);
    return get(i0 - startingPos_[0]);
  }

  V& operator()(int i0, int i1) {
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
}

#endif
