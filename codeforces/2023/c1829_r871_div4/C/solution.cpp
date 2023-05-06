#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int INF = 1e9;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> t1;
        vector<int> t2;
        vector<int> t12;

        for (int i = 1; i <= n; ++i) {
            int x;
            cin >> x;

            string bits;
            cin >> bits;

            if (bits == "10") {
                t1.push_back(x);
            } else if (bits == "01") {
                t2.push_back(x);
            } else if (bits == "11") {
                t12.push_back(x);
            }
        }

        const auto lo1 = t1.empty() ? INF : *min_element(cbegin(t1), cend(t1));
        const auto lo2 = t2.empty() ? INF : *min_element(cbegin(t2), cend(t2));
        const auto lo12 =
            t12.empty() ? INF : *min_element(cbegin(t12), cend(t12));

        int ans = lo12;
        if (lo1 != INF && lo2 != INF) {
            ans = min(ans, lo1 + lo2);
        }

        cout << (ans == INF ? -1 : ans) << '\n';
    }

    return 0;
}
