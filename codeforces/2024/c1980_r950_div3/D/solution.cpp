#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

optional<int> first_offending_index(const vector<int> &xs) {
    const auto n = sz(xs);
    vector<int> ys(n - 1, 0);
    for (int i = 0; i < n - 1; ++i) {
        ys[i] = std::gcd(xs[i], xs[i + 1]);
    }
    if (is_sorted(cbegin(ys), cend(ys))) return nullopt;

    for (int i = 1; i < n - 1; ++i) {
        if (ys[i] < ys[i - 1]) return i;
    }
    assert(false && "/o\\");
    return nullopt;
}

bool can_remove_one(const vector<int> &xs) {
    const auto oi = first_offending_index(xs);
    if (!oi) return true;

    if (*oi < sz(xs)) {
        auto ys = xs;
        ys.erase(cbegin(ys) + (*oi));
        if (!first_offending_index(ys)) return true;
    }

    if (0 <= *oi - 1 && *oi - 1 < sz(xs)) {
        auto ys = xs;
        ys.erase(cbegin(ys) + (*oi) - 1);
        if (!first_offending_index(ys)) return true;
    }

    if (0 <= *oi + 1 && *oi + 1 < sz(xs)) {
        auto ys = xs;
        ys.erase(cbegin(ys) + (*oi) + 1);
        if (!first_offending_index(ys)) return true;
    }

    return false;
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

        cout << (can_remove_one(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
