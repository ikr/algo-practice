#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

array<int, 11> gather_freqs(const vector<int> &xs) {
    array<int, 11> result{};
    result.fill(0);
    for (const auto x : xs) ++result[x];
    return result;
}

pair<int, int> evs_ods(const array<int, 11> &fs) {
    int evs{};
    int ods{};

    for (int x = 1; x <= 10; ++x) {
        if (fs[x] == 0) continue;
        if (x % 2 == 0) {
            evs += fs[x];
        } else {
            ods += fs[x];
        }
    }

    return {evs, ods};
}

int min_ops_2(const vector<int> &xs) {
    const auto fs = gather_freqs(xs);
    const auto [evs, ods] = evs_ods(fs);
    if (evs) return 0;
    return 1;
}

int min_ops_3(const vector<int> &xs) {
    const auto fs = gather_freqs(xs);
    if (fs[3] || fs[6] || fs[9]) return 0;
    if (fs[2] || fs[5] || fs[8]) return 1;
    return 2;
}

int min_ops_4(const vector<int> &xs) {
    const auto fs = gather_freqs(xs);
    const auto [evs, ods] = evs_ods(fs);
    if (evs >= 2 || fs[4] || fs[8]) return 0;
    if (fs[3] || fs[7] || evs == 1) return 1;
    return 2;
}

int min_ops_5(const vector<int> &xs) {
    const auto fs = gather_freqs(xs);
    if (fs[5] || fs[10]) return 0;
    if (fs[4] || fs[9]) return 1;
    if (fs[3] || fs[8]) return 2;
    if (fs[2] || fs[7]) return 3;
    return 4;
}

int min_ops(const vector<int> &xs, const int k) {
    switch (k) {
    case 2:
        return min_ops_2(xs);
    case 3:
        return min_ops_3(xs);
    case 4:
        return min_ops_4(xs);
    default:
        assert(k == 5);
        return min_ops_5(xs);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << min_ops(xs, k) << '\n';
    }

    return 0;
}
