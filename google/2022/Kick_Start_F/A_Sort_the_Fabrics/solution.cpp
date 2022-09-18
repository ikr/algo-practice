#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int matches(const vector<tuple<string, int, int>> &fs) {
    auto ada = fs;
    sort(begin(ada), end(ada), [](const auto &a, const auto &b) {
        const auto &[ca, _1, ua] = a;
        const auto &[cb, _2, ub] = b;

        if (ca == cb) return ua < ub;
        return ca < cb;
    });

    auto cha = fs;
    sort(begin(cha), end(cha), [](const auto &a, const auto &b) {
        const auto &[_1, da, ua] = a;
        const auto &[_2, db, ub] = b;

        if (da == db) return ua < ub;
        return da < db;
    });

    int result{};
    for (int i = 0; i < sz(fs); ++i) {
        result += ada[i] == cha[i];
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<tuple<string, int, int>> fs(N);
        for (auto &[c, d, u] : fs) {
            cin >> c >> d >> u;
        }

        cout << "Case #" << i << ": " << matches(fs) << '\n';
    }

    return 0;
}
