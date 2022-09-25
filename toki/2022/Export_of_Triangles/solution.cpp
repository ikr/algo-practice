#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<int> &xs) {
    for (int i = 0; i < sz(xs); ++i) {
        for (int j = 0; j < sz(xs); ++j) {
            if (i == j) continue;
            if ((xs[i] * xs[j]) % 2 == 0) return true;
        }
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    cout << (is_possible(xs) ? "YA" : "TIDAK") << '\n';
    return 0;
}
