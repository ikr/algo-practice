#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<int> &xs) {
    const auto twos = inof(count(cbegin(xs), cend(xs), 2));
    return (twos % 8) == 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << (is_possible(xs) ? "YES\n" : "NO\n");
    }

    return 0;
}
