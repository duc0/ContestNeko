#include "global.hpp"

#ifndef H_SCANNER
#define H_SCANNER

#ifdef IO_USE_CSTDIO

class Scanner {
    std::istream &in;

public:
    Scanner(std::istream &in) : in(in) {
    }

    int read(int &result) {
        scanf("%d", &result);
    }
};

class Writer {
    std::ostream &out;

public:
    Writer(std::ostream &out) : out(out) {
    }

    void write(int value) {
        printf("%d", value);
    }
};

#else

class Scanner {
    std::istream &in;

public:
    Scanner(std::istream &in) : in(in) {
    }

    template <class T> void read(T &result) {
        in >> result;
    }
};

class Writer {
    std::ostream &out;

public:
    Writer(std::ostream &out) : out(out) {
    }

    template <class T> void write(T value) {
        out << value;
    }
};
#endif

#endif