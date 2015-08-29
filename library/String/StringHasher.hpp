#include "global.hpp"

template <int BASE, int MODULO> class BasePowerUtils {

public:
    static int getBasePower(int n) {
        static vector<int> power; // cache
        if (n > (int)power.size() - 1) {
            int cur = (int)power.size() - 1;
            power.resize(n + 1);
            for_inc_range(i, cur + 1, n) {
                if (i == 0) {
                    power[i] = 1;
                } else {
                    power[i] = ((int64)power[i - 1] * BASE) % MODULO;
                }
            }
        }
        return power[n];
    }
};


template <int BASE, int MODULO> class StringHash {
    int length;
    int hash;
public:
    int getLength() const {
        return length;
    }

    int getHash() const {
        return hash;
    }

    StringHash(int hash, int length): hash(hash), length(length) {}

    template <class Iterator> StringHash(Iterator begin, Iterator end) {
        hash = 0;
        for (auto it = begin; it != end; ++it) {
            hash = ((int64)hash * BASE + *it) % MODULO;
        }
        length = (int) (end - begin);
    }

    static StringHash<BASE, MODULO> fromSingleChar(int singleChar) {
        return StringHash<BASE, MODULO>(singleChar % MODULO, 1);
    }

    StringHash<BASE, MODULO> concat(const StringHash<BASE, MODULO> &sh) const {
        return StringHash<BASE, MODULO>(((int64) getHash() * BasePowerUtils<BASE, MODULO>::getBasePower(sh.getLength()) +
                                         sh.getHash()) % MODULO, getLength() + sh.getLength());
    }
};

template <int BASE, int MODULO> class StringPrefixHash {
    vector<int> hash;

public:
    StringPrefixHash() {}

    template <class Iterator> StringPrefixHash(Iterator begin, Iterator end) {
        int n = (int)(end - begin);
        hash.resize(n);
        int idx = 0;
        int last = 0;
        for (auto it = begin; it != end; ++it) {
            hash[idx] = ((int64)last * BASE + *it) % MODULO;
            last = hash[idx];
            idx++;
        }
    }

    size_t getSize() const { return hash.size(); }

    StringHash<BASE, MODULO> getPrefixHash(int i) const {
        assert(i < getSize());
        return StringHash<BASE, MODULO>(hash[i], i);
    }

    StringHash<BASE, MODULO> getStringHash() const {
        return getPrefixHash(hash.size() - 1);
    }

    StringHash<BASE, MODULO> getSubstringHash(int first, int len) const {
        if (len == 0) return StringHash<BASE, MODULO>(0, 0);
        assert(0 <= first && first < getSize());
        assert(len >= 1);
        assert(first + len - 1 < getSize());
        int last = first + len - 1;
        if (first == 0) {
            return StringHash<BASE, MODULO>(hash[last], len);
        }
        int ret = (hash[last] - (int64) hash[first - 1] * BasePowerUtils<BASE, MODULO>::getBasePower(len)) % MODULO;
        if (ret < 0)
            ret += MODULO;
        return StringHash<BASE, MODULO>(ret, len);
    }

    // Range is inclusive
    StringHash<BASE, MODULO> getSubstringHashByRange(int first, int last) const {
        return getSubstringHash(first, last - first + 1);
    }
};

template <int BASE1, int MODULO1, int BASE2, int MODULO2> class StringDoubleHash {
    int length;
    int hash1;
    int hash2;
public:
    int getLength() const {
        return length;
    }

    int64 getHashValue() const {
        return (int64) hash1 * MODULO2 + hash2;
    }

    StringHash<BASE1, MODULO1> getHash1() const {
        return StringHash<BASE1, MODULO1>(hash1, length);
    }

    StringHash<BASE2, MODULO2> getHash2() const {
        return StringHash<BASE2, MODULO2>(hash2, length);
    }

    StringDoubleHash(int hash1, int hash2, int length): hash1(hash1), hash2(hash2), length(length) {}

    StringDoubleHash(const StringHash<BASE1, MODULO1> &h1, const StringHash<BASE2, MODULO2> &h2): hash1(h1.getHash()), hash2(h2.getHash()), length(h1.getLength()) {
        assert(h1.getLength() == h2.getLength());
    }

    template <class Iterator> StringDoubleHash(Iterator begin, Iterator end) {
        hash1 = StringHash<BASE1, MODULO1>(begin, end).getHash();
        hash2 = StringHash<BASE2, MODULO2>(begin, end).getHash();
        length = (int) (end - begin);
    }

    static StringDoubleHash<BASE1, MODULO1, BASE2, MODULO2> fromSingleChar(int singleChar) {
        return StringDoubleHash<BASE1, MODULO1, BASE2, MODULO2>(singleChar % MODULO1, singleChar % MODULO2, 1);
    }

    StringDoubleHash<BASE1, MODULO1, BASE2, MODULO2> concat(const StringDoubleHash<BASE1, MODULO1, BASE2, MODULO2> &sh) const {
        return StringDoubleHash<BASE1, MODULO1, BASE2, MODULO2>(
                getHash1().concat(sh.getHash1()),
                getHash2().concat(sh.getHash2())
        );
    }
};


template <int BASE1, int MODULO1, int BASE2, int MODULO2> class StringPrefixDoubleHash {
    StringPrefixHash<BASE1, MODULO1> hash1;
    StringPrefixHash<BASE2, MODULO2> hash2;

public:
    StringPrefixDoubleHash() {}

    template <class Iterator> StringPrefixDoubleHash(Iterator begin, Iterator end): hash1(StringPrefixHash<BASE1, MODULO1>(begin, end)), hash2(StringPrefixHash<BASE2, MODULO2>(begin, end)) {}

    size_t getSize() const { return hash1.getSize(); }

    StringDoubleHash<BASE1, MODULO1, BASE2, MODULO2> getPrefixHash(int i) const {
        return StringDoubleHash<BASE1, MODULO1, BASE2, MODULO2>(hash1.getPrefixHash(i), hash2.getPrefixHash(i));
    }

    StringDoubleHash<BASE1, MODULO1, BASE2, MODULO2> getStringHash() const {
        return getPrefixHash((int)getSize() - 1);
    }

    StringDoubleHash<BASE1, MODULO1, BASE2, MODULO2> getSubstringHash(int first, int len) const {
        return StringDoubleHash<BASE1, MODULO1, BASE2, MODULO2>(hash1.getSubstringHash(first, len), hash2.getSubstringHash(first, len));
    }

    // Range is inclusive
    StringDoubleHash<BASE1, MODULO1, BASE2, MODULO2> getSubstringHashByRange(int first, int last) const {
        return getSubstringHash(first, last - first + 1);
    }
};

vector<int> lowercaseStringToVector(const string &s) {
    vector<int> a;
    for (char c : s) {
        a.push_back(c - 'a');
    }
    return a;
}