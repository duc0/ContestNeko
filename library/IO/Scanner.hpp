#include "global.hpp"

#ifndef H_SCANNER
#define H_SCANNER


class Scanner {
 public:
  Scanner(std::istream& inStream) : inStream_(inStream) {
    ios_base::sync_with_stdio(false);
  }

  int nextInt() const {
    int result;
    inStream_ >> result;
    return result;
  }

  int64 nextLong() const {
    int64 result;
    inStream_ >> result;
    return result;
  }

  string nextString() const {
    string result;
    inStream_ >> result;
    return result;
  }

 private:
  std::istream& inStream_;
};

class IWriter {
 public:
  virtual void write(int val) const = 0;

  virtual void write(int64 val) const = 0;

  virtual void newLine() const = 0;
};

class CWriter: IWriter {
 public:
  CWriter(std::ostream& outStream) {
    ios_base::sync_with_stdio(false);
  }

  void write(int val) const {
    cout << val;
  }

  void write(int64 val) const {
    cout << val;
  }

  void newLine() const {
    cout << "\n";
  }
};

class StreamWriter: IWriter {
 public:
  StreamWriter(std::ostream& outStream) : outStream_(outStream) {
  }

  void write(int val) const {
    outStream_ << val;
  }

  void write(int64 val) const {
    outStream_ << val;
  }

  void newLine() const {
    outStream_ << "\n";
  }

 private:
  std::ostream& outStream_;
};

#ifdef IO_USE_CSTDIO
using Writer = CWriter;
#else
using Writer = StreamWriter;
#endif

#endif