#include <bits/stdc++.h>
using namespace std;
static constexpr long long X_MAX = 1'000'000'000'000LL;

bool representable(const set<long long> &cs, const long long x) {
    for (const auto q : cs) {
        if (cs.count(x - q)) return true;
    }

    return false;
}

set<long long> gather_cubes() {
    set<long long> ans;
    for (long long i = 1LL; i * i * i <= X_MAX; ++i) {
        ans.insert(i * i * i);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    const auto cs = gather_cubes();

    int t;
    cin >> t;
    while (t--) {
        long long x;
        cin >> x;

        cout << (representable(cs, x) ? "YES\n" : "NO\n");
    }

    return 0;
}
