#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, T;
    cin >> N >> T;

    vector<int> C(N);
    for (auto &c : C) cin >> c;

    vector<int> R(N);
    for (auto &r : R) cin >> r;

    const set<int> colors(cbegin(C), cend(C));
    const auto winning_color = colors.count(T) ? T : C[0];

    int hi = 0;
    int ans = -1;

    for (int i = 0; i < N; ++i) {
        if (C[i] != winning_color) continue;
        if (R[i] > hi) {
            hi = R[i];
            ans = i;
        }
    }

    assert(ans >= 0);
    cout << (ans + 1) << '\n';
    return 0;
}
