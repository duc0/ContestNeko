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

#ifdef IO_USE_CSTDIO

using Scanner = CScanner;

class Writer {
    std::ostream &out;

public:
    Writer(std::ostream &out) : out(out) {
    }

    Writer& operator << (int value) {
        printf("%d", value);
        return *this;
    }

    Writer& operator << (int64 value) {
        printf("%I64d", value);
        return *this;
    }

    Writer& operator << (string &value) {
        printf("%s", value.c_str());
        return *this;
    }

    Writer& operator << (const char *value) {
        printf("%s", value);
        return *this;
    }

    Writer& newline() {
        printf("\n");
        return *this;
    }
};

#else

using Scanner = StreamScanner;

class Writer {
    std::ostream &out;

public:
    Writer(std::ostream &out) : out(out) {
    }

    template <class T> Writer& operator << (T value) {
        out << value;
        return *this;
    }

    Writer& newline() {
        out << endl;
        return *this;
    }
};
#endif

#endif