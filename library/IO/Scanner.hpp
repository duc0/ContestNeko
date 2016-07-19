#include "global.hpp"

#ifndef H_SCANNER
#define H_SCANNER

#ifdef IO_USE_CSTDIO

class Scanner {
    std::istream &in;

public:
    Scanner(std::istream &in) : in(in) {
    }

    Scanner& operator >> (int &result) {
        scanf("%d", &result);
        return *this;
    }

    Scanner& operator >> (int64 &result) {
        scanf("%I64d", &result);
        return *this;
    }
};

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

class Scanner {
    std::istream &in;

public:
    Scanner(std::istream &in) : in(in) {
    }

    template <class T> Scanner& operator >> (T &result) {
        in >> result;
        return *this;
    }
};

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