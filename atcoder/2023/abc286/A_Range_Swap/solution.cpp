#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, P, Q, R, S;
    cin >> N >> P >> Q >> R >> S;
    --P;
    --Q;
    --R;
    --S;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    for (int i = P, j = R; i <= Q && j <= S; ++i, ++j) {
        swap(xs[i], xs[j]);
    }

    cout << xs << '\n';
    return 0;
}
