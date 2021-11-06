#include <bits/stdc++.h>

using namespace std;

using Int = long long;
static const Int M = 1e9 + 7;

struct Solution final {
    int numOfWays(const int n) const {
        vector<Int> dp_duo(n + 1, 6);
        vector<Int> dp_tri(n + 1, 6);

        for (int i = 2; i <= n; ++i) {
            dp_tri[i] = (2 * dp_tri[i - 1] + 2 * dp_duo[i - 1]) % M;
            dp_duo[i] = (2 * dp_tri[i - 1] + 3 * dp_duo[i - 1]) % M; 
        }

        return (dp_duo[n] + dp_tri[n]) % M;
    }
};

int main() {
    assert(Solution{}.numOfWays(1) == 12);
    assert(Solution{}.numOfWays(2) == 54);
    assert(Solution{}.numOfWays(3) == 246);
    assert(Solution{}.numOfWays(7) == 106494);
    assert(Solution{}.numOfWays(5000) == 30228214);

    return 0;
}
