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

vector<int> gather_index(const vector<int> &xs) {
    const int n = xs.size();
    vector<int> ans(n, -1);
    for (int i = 0; i < n; ++i) ans[xs[i]] = i;
    return ans;
}

vector<int> gather_suff_max_b(const vector<pair<int, int>> &fs,
                              const vector<int> &by_a) {
    const int n = fs.size();
    vector<int> suff_max_b(n, fs[by_a.back()].second);

    for (int i = n - 2; i >= 0; --i) {
        suff_max_b[i] = max(suff_max_b[i + 1], fs[by_a[i]].second);
    }

    return suff_max_b;
}

vector<int> in_fronts(vector<pair<int, int>> fs) {
    const int n = fs.size();
    const auto by_a = gather_by_a(fs);
    const auto by_a_idx = gather_index(by_a);
    const auto suff_max_b = gather_suff_max_b(fs, by_a);

    vector<int> ans(n, -1);

    for (int i = 0; i < n; ++i) {
        if (fs[i].first == fs[by_a.back()].first) continue;

        const auto it = partition_point(
            cbegin(by_a) + by_a_idx[i], cend(by_a),
            [&](const auto j) { return fs[by_a[j]].first == fs[i].first; });

        if (it == cend(by_a)) continue;

        // TODO
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

        for (auto &[a, b] : fs) {
            int h, w;
            cin >> h >> w;

            a = max(h, w);
            b = min(h, w);
        }

        cout << in_fronts(move(fs)) << '\n';
    }

    return 0;
}
