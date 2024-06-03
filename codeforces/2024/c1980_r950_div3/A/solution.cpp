#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int missing_count(const int m, const string &xs) {
    vector<int> fs(7, 0);
    for (const auto x : xs) ++fs[inof(x) - inof('A')];

    int result{};
    for (const auto f : fs) {
        if (f < m) {
            result += m - f;
        }
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << missing_count(m, xs) << '\n';
    }

    return 0;
}
