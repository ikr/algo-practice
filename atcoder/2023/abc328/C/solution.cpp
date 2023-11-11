#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, Q;
    cin >> N >> Q;

    string xs;
    cin >> xs;
    assert(sz(xs) == N);

    vector<int> idx;
    for (int i = 1; i < N; ++i) {
        if (xs[i - 1] == xs[i]) {
            idx.push_back(i - 1);
        }
    }

    for (int q = 1; q <= Q; ++q) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;

        const auto a = ranges::lower_bound(idx, l) - cbegin(idx);
        const auto b = ranges::lower_bound(idx, r) - cbegin(idx);
        cout << b - a << '\n';
    }

    return 0;
}
