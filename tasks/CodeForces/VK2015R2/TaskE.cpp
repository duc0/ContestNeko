#include "global.hpp"
#include "StringHasher.hpp"

#define B1 31
#define B2 37
#define HMOD1 1000001927
#define HMOD2 1000001963
#define SH StringDoubleHash<B1, HMOD1, B2, HMOD2>
#define SPH StringPrefixDoubleHash<B1, HMOD1, B2, HMOD2>

vector<int64> getAll(const vector<int> &s, int n) {
    SPH h(s.begin(), s.end());

    vector<int64> ans;
    for_inc_range(i, 0, n) {
        for_inc(c, 26) {
            auto dh = h.getSubstringHashByRange(0, i - 1);
            dh = dh.concat(SH::fromSingleChar(c));
            dh = dh.concat(h.getSubstringHashByRange(i, n - 1));
            ans.push_back(dh.getHashValue());
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}

class TaskE {
public:
    void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        string ss1, ss2;
        in >> ss1 >> ss2;

        vector<int> s1(n);
        for_inc(i, n) s1[i] = ss1[i] - 'a';
        vector<int> s2(n);
        for_inc(i, n) s2[i] = ss2[i] - 'a';

        vector<int64> all1 = getAll(s1, n);
        vector<int64> all2 = getAll(s2, n);

        unique(all1.begin(), all1.end());
        unique(all2.begin(), all2.end());

        vector<int64> inter(max(all1.size(), all2.size()));
        auto it=set_intersection (all1.begin(), all1.end(), all2.begin(), all2.end(), inter.begin());
        out << (it - inter.begin());
    }
};
