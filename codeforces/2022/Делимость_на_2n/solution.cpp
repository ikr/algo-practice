#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int contained_twos(int x) {
    int result{};

    while (x % 2 == 0) {
        ++result;
        x /= 2;
    }

    return result;
}

int min_ops(const vector<int> &xs) {
    const auto n = sz(xs);

    int curr{};
    for (const auto x : xs) {
        curr += contained_twos(x);
    }

    if (curr >= n) return 0;

    vector<int> positions(n);
    iota(begin(positions), end(positions), 1);
    sort(begin(positions), end(positions), [&](const int a, const int b) {
        return contained_twos(a) > contained_twos(b);
    });

    int result{};

    for (const auto pos : positions) {
        curr += contained_twos(pos);
        ++result;
        if (curr >= n) break;
    }

    return curr >= n ? result : -1;
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

        cout << min_ops(xs) << '\n';
    }

    return 0;
}
