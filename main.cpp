// Paste me into the FileEdit configuration dialog

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define MOD 1000000007
#define int64 long long

class TaroFillingAStringDiv1 {
public:
    int getNumber(int n, vector <int> pos, string val ) {
        vector<pair<int, char>> a;
        
        int k = (int)pos.size();
        for (int i = 0; i < k; ++i) {
            int p = pos[i];
            char c = val[i];
            a.push_back(make_pair(p, c));
        }
        sort(a.begin(), a.end());
        
        int ret = 1;
        for (int i = 1; i < k; ++i) {
            int diff = a[i].first - a[i - 1].first - 1;
            if (diff % 2 == 0) {
                if (a[i].second != a[i - 1].second) {
                    continue;
                }
                ret = ((int64)ret * (diff + 1)) % MOD;
            } else {
                if (a[i].second == a[i - 1].second) {
                    continue;
                }
                ret = ((int64)ret * (diff + 1)) % MOD;
            }
            
        }
        return ret;
    }
};



// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor


// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor