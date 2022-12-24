#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> indices_by_value(const vector<int> &xs) {
    vector<int> result(sz(xs) + 1, -1);
    for (int i = 0; i < sz(xs); ++i) {
        result[xs[i]] = i;
    }
    return result;
}

vector<int> find_ds(const vector<int> &P) {
    const auto N = sz(P);
    const auto idx = indices_by_value(P);
    vector<int> ans(N, INT_MAX);

    for (int i = 0; i < N; ++i) {
        const auto p = P[i];

        for (int j = 1; j < 1000; ++j) {
            if (p - j >= 1) ans[i] = min(ans[i], j + abs(i - idx[p - j]));
            if (p + j <= N) ans[i] = min(ans[i], j + abs(i - idx[p + j]));
            if (i - j >= 0) ans[i] = min(ans[i], abs(P[i] - P[i - j]) + j);
            if (i + j < N) ans[i] = min(ans[i], abs(P[i] - P[i + j]) + j);
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> P(N);
    for (auto &p : P) cin >> p;

    cout << find_ds(P) << '\n';
    return 0;
}
