#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<char, int>> run_length_encode(const string &xs) {
    vector<pair<char, int>> ans{{xs[0], 1}};
    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] == ans.back().first) {
            ++(ans.back().second);
        } else {
            ans.emplace_back(xs[i], 1);
        }
    }
    return ans;
}

int max_coins(const string &xs) {
    const auto rle = run_length_encode(xs);
    if (sz(rle) == 1) return 0;

    vector<int> a_lengths;
    for (const auto &[x, len] : rle) {
        if (x == 'A') a_lengths.push_back(len);
    }
    ranges::sort(a_lengths);
    const auto A = accumulate(cbegin(a_lengths), cend(a_lengths), 0);

    if (rle[0].first == 'B' || rle.back().first == 'B') return A;
    return A - a_lengths[0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;
        cout << max_coins(xs) << '\n';
    }
    return 0;
}
