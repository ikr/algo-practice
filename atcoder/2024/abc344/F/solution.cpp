#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<vector<int>> P(N, vector(N, 0));
    for (auto &row : P) {
        for (auto &p : row) cin >> p;
    }

    vector<vector<int>> R(N, vector(N - 1, 0));
    for (auto &row : R) {
        for (auto &r : row) cin >> r;
    }

    vector<vector<int>> D(N - 1, vector(N, 0));
    for (auto &row : D) {
        for (auto &d : row) cin >> d;
    }

    return 0;
}
