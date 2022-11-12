#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<int, int> gather_freqs(const vector<int> &xs) {
    map<int, int> result;
    for (const auto x : xs) ++result[x];
    return result;
}

ll min_remaining_sum(const vector<int> &A, const int M) {
    const auto fs = gather_freqs(A);

    vector<int> vert;
    vert.reserve(sz(fs));
    for (const auto [a, _] : fs) {
        vert.push_back(a);
    }

    map<int, int> idx;
    for (int i = 0; i < sz(vert); ++i) {
        idx[vert[i]] = i;
    }

    vector<vector<int>> g(sz(vert));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    cout << min_remaining_sum(A, M) << '\n';
    return 0;
}
