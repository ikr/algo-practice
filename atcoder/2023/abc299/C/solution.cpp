#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<char, int>> run_length_encode(const string &xs) {
    vector<pair<char, int>> ans{{xs[0], 1}};
    for (int i = 1; i < sz(xs); ++i) {
        if (ans.back().first == xs[i]) {
            ++(ans.back().second);
        } else {
            ans.emplace_back(xs[i], 1);
        }
    }
    return ans;
}

int find_greatest_x(string xs) {
    const auto rle = run_length_encode(xs);
    int ans{};
    for (int i = 0; i < sz(rle); ++i) {
        if (rle[i].first == 'o' && (i || i < sz(rle) - 1)) {
            ans = max(ans, rle[i].second);
        }
    }
    return ans ? ans : -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    string xs;
    cin >> xs;
    assert(sz(xs) == N);

    cout << find_greatest_x(move(xs)) << '\n';
    return 0;
}
