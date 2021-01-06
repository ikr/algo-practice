#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> gather_by_a(const vector<pair<int, int>> &fs) {
    const int n = fs.size();

    vector<int> by_a(n);
    iota(begin(by_a), end(by_a), 0);

    sort(begin(by_a), end(by_a), [&](const auto lhs, const auto rhs) {
        return fs[lhs].first > fs[rhs].first;
    });

    return by_a;
}

vector<pair<int, int>> gather_suff_min_b(const vector<pair<int, int>> &fs,
                                         const vector<int> &by_a) {
    const int n = fs.size();
    vector<pair<int, int>> suff_min_b(n, {fs[by_a.back()].second, n - 1});

    for (int i = n - 2; i >= 0; --i) {
        suff_min_b[i] = suff_min_b[i + 1].first <= fs[by_a[i]].second
                            ? suff_min_b[i + 1]
                            : pair{fs[by_a[i]].second, i};
    }

    return suff_min_b;
}

template <typename T> constexpr pair<T, T> flip_pair(const pair<T, T> &ab) {
    return {ab.second, ab.first};
}

vector<int> in_fronts(vector<pair<int, int>> fs) {
    const int n = fs.size();
    const auto by_a = gather_by_a(fs);
    const auto suff_min_b = gather_suff_min_b(fs, by_a);

    const auto suggest_in_front = [&](const int i,
                                      const pair<int, int> ab) -> int {
        if (ab.first == fs[by_a.back()].first) return -1;

        const auto it = partition_point(
            cbegin(by_a) + i, cend(by_a),
            [&](const auto j) { return fs[by_a[j]].first == ab.first; });

        if (it == cend(by_a)) return -1;

        const int j = distance(cbegin(by_a), it);
        const auto [min_b, k] = suff_min_b[j];
        if (min_b >= ab.second) return -1;
        return by_a[k];
    };

    vector<int> ans(n, -1);

    for (int i = 0; i < n; ++i) {
        const int o1 = suggest_in_front(i, fs[by_a[i]]);
        if (o1 >= 0) {
            ans[by_a[i]] = o1 + 1;
            continue;
        }

        const int o2 = suggest_in_front(i, flip_pair(fs[by_a[i]]));
        if (o2 >= 0) ans[by_a[i]] = o2 + 1;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pair<int, int>> fs(n);
        for (auto &[a, b] : fs) cin >> a >> b;
        cout << in_fronts(move(fs)) << '\n';
    }

    return 0;
}
