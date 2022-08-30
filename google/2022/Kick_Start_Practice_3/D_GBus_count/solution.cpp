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

vector<int> coverage(const vector<pair<int, int>> &AB, const vector<int> &C) {
    map<int, int> incs;
    map<int, int> decs;

    for (const auto &[a, b] : AB) {
        ++incs[a];
        ++decs[b + 1];
    }

    vector<int> xs(5002, 0);
    for (int i = 0, cur = 0; i < sz(xs); ++i) {
        cur += incs[i];
        cur -= decs[i];
        xs[i] = cur;
    }

    vector<int> result(sz(C));
    transform(cbegin(C), cend(C), begin(result),
              [&xs](const int c) { return xs[c]; });
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<pair<int, int>> AB(N);
        for (auto &[a, b] : AB) {
            cin >> a >> b;
            if (a > b) swap(a, b);
        }

        int P;
        cin >> P;

        vector<int> C(P);
        for (auto &c : C) cin >> c;

        cout << "Case #" << i << ": " << coverage(AB, C) << '\n';
    }

    return 0;
}
