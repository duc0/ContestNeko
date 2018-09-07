#include "global.hpp"

#ifndef H_SCANNER
#define H_SCANNER

class IScanner {
public:
    virtual int nextInt() const = 0;
};

class CScanner : IScanner {
public:
    CScanner(std::istream& inStream) {
    }

    int nextInt() const {
        int result;
        scanf("%d", &result);
        return result;
    }
};

class StreamScanner : IScanner {
public:
    StreamScanner(std::istream& inStream) : inStream_(inStream) {
    }

    int nextInt() const {
        int result;
        inStream_ >> result;
        return result;
    }

private:
    std::istream& inStream_;
};

class IWriter {
public:
    virtual void write(int val) const = 0;
};


class CWriter : IWriter {
public:
    CWriter(std::ostream& outStream) {
    }

    void write(int val) const {
        printf("%d", val);
    }
};

class StreamWriter : IWriter {
public:
    StreamWriter(std::ostream& outStream) : outStream_ (outStream) {
    }

    void write(int val) const {
        outStream_ << val;
    }

private:
    std::ostream& outStream_;
};

#ifdef IO_USE_CSTDIO
using Scanner = CScanner;
using Writer = CWriter;
#else
using Scanner = StreamScanner;
using Writer = StreamWriter;
#endif

#endif