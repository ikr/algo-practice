#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> gather_frequencies(const vector<int> &xs) {
    vector<vector<int>> freq{{1}};
    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i - 1] == xs[i]) {
            ++freq.back().back();
        } else if (xs[i - 1] + 1 == xs[i]) {
            freq.back().push_back(1);
        } else {
            freq.push_back({1});
        }
    }
    return freq;
}

mint magnificent_groups_count_of_a_span(const vector<int> &freq, const int m) {
    if (sz(freq) < m) return 0;
    auto cur = accumulate(cbegin(freq), cbegin(freq) + m, mint{1},
                          [](const mint &a, const mint &b) { return a * b; });
    auto result = cur;
    for (int i = 1; i + m <= sz(freq); ++i) {
        cur *= mint{freq[i - 1]}.inv();
        cur *= freq[i + m - 1];
        result += cur;
    }
    return result;
}

mint magnificent_groups_count(const vector<int> &xs, const int m) {
    const auto freq = gather_frequencies(xs);
    return transform_reduce(
        cbegin(freq), cend(freq), mint{0},
        [](const mint &a, const mint &b) { return a + b; },
        [&](const auto &sub) {
            return magnificent_groups_count_of_a_span(sub, m);
        });
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        cout << magnificent_groups_count(xs, m).val() << '\n';
    }

    return 0;
}
