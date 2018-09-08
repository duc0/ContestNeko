#include "global.hpp"
#include "Collections.hpp"

#ifndef H_SCANNER
#define H_SCANNER


class Scanner {
 public:
  Scanner(std::istream& inStream) : inStream_(inStream) {
    ios_base::sync_with_stdio(false);
  }

  template<typename T> cl::NDArray<T> nextArray(int size, int startingPos = 0, T defaultValue = 0) {
    auto result = cl::NDArray<T>({size}, defaultValue, startingPos);
    FOR_INC(i, size) {
      T x = next<T>();
      result(startingPos + i) = x;
    }
    return result;
  }

  template<typename T> T next() const {
    T result;
    inStream_ >> result;
    return result;
  }

 private:
  std::istream& inStream_;
};


class Writer {
 public:
  Writer(std::ostream& outStream) : outStream_(outStream) {
  }

  template <typename T> void write(T val) const {
    outStream_ << val;
  }

  void newLine() const {
    outStream_ << "\n";
  }

 private:
  std::ostream& outStream_;
};

#endif