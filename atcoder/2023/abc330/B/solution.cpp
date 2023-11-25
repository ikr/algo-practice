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

    int N, L, R;
    cin >> N >> L >> R;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    vector<int> X;
    X.reserve(N);

    for (const auto a : A) {
        if (a < L) {
            X.push_back(L);
        } else if (a > R) {
            X.push_back(R);
        } else {
            X.push_back(a);
        }
    }

    cout << X << '\n';
    return 0;
}
