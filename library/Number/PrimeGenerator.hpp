#include "global.hpp"
#include "NumberTheory.hpp"

class PrimeGenerator {
    vector<bool> prime;
    vector<int> primeList;
    int upper;
public:
    // Generate all primes between 2 and upper
    PrimeGenerator(int upper) {
        assert(upper >= 2);
        this->upper = upper;

        prime.resize(upper + 1);
        for_inc_range(i, 0, upper) {
            prime[i] = true;
        }
        prime[0] = prime[1] = false;
        for (int i = 2; i * i <= upper; ++i) {
            if (prime[i]) {
                for (int j = i * i; j <= upper; j += i) {
                    prime[j] = false;
                }
            }
        }

        for_inc_range(i, 2, upper) {
            if (prime[i]) {
                primeList.push_back(i);
            }
        }
    }

    // O(1)
    bool isPrime(int n) const {
        assert(n <= upper);
        if (n < 2) {
            return false;
        }
        return prime[n];
    }

    // Get 1-based prime, e.g. getPrime(1) = 2, getPrime(2) = 3,...
    int getPrime(int id) const {
        assert(id >=1 && id <= primeList.size());
        return primeList[id - 1];
    }

    const vector<int> &getPrimeList() const {
        return primeList;
    }
};