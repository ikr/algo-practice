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

vector<vector<pair<char, int>>>
slice_on_multi_Bs(const vector<pair<char, int>> &rle) {
    vector<vector<pair<char, int>>> result;
    result.push_back({});

    for (const auto &[x, f] : rle) {
        if (x == 'B' && f > 1) {
            result.back().push_back({'B', 1});
            result.push_back({{'B', 1}});
        } else {
            result.back().push_back({x, f});
        }
    }

    return result;
}

int max_coins(const vector<pair<char, int>> &rle) {
    vector<int> a_lengths;
    for (const auto &[x, len] : rle) {
        if (x == 'A') a_lengths.push_back(len);
    }
    ranges::sort(a_lengths);
    const auto A = accumulate(cbegin(a_lengths), cend(a_lengths), 0);

    if (rle[0].first == 'B' || rle.back().first == 'B') return A;
    return A - a_lengths[0];
}

int max_coins(const string &xs) {
    const auto rle = run_length_encode(xs);
    if (sz(rle) == 1) return 0;

    const auto slices = slice_on_multi_Bs(rle);
    return accumulate(
        cbegin(slices), cend(slices), 0,
        [](const int acc, const auto &x) { return acc + max_coins(x); });
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
