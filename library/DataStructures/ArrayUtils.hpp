#include "global.hpp"
#include "NDArray.hpp"

#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

namespace utils {
  template <typename T> cl::NDArray<T> getSumArray(const cl::NDArray<T>& a) {
    assert(a.getDimension() == 1);
    assert(a.startingPos(0) == 1);
    int l = a.getSize();
    auto result = cl::NDArray<T>({l + 1}, 0);
    FOR_INC_RANGE(i, 1, l) {
      result(i) = result(i - 1) + a(i);
    }
    return result;
  }
}

#endif
