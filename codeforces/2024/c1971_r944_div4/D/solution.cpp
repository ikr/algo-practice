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

int min_pieces(const string &xs) {
    const auto rle = run_length_encode(xs);
    if (sz(rle) == 1) return 1;

    if (sz(rle) == 2) {
        return rle[0].first == '0' ? 1 : 2;
    }

    return sz(rle) - 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;
        cout << min_pieces(xs) << '\n';
    }

    return 0;
}
