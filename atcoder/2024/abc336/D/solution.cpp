#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> A(n);
    for (auto &a : A) cin >> a;

    vector<int> ls(n, 0);
    for (int i = 1; i < n; ++i) {
        if (A[i] > A[i - 1]) {
            ls[i] = ls[i - 1] + 1;
            continue;
        }

        if (A[i] > ls[i - 1] + 1) {
            ls[i] = ls[i - 1] + 1;
            continue;
        }

        ls[i] = min(ls[i - 1], A[i] - 1);
    }

    vector<int> rs(n, 0);
    for (int i = n - 2; i >= 0; --i) {
        if (A[i] > A[i + 1]) {
            rs[i] = rs[i + 1] + 1;
            continue;
        }

        if (A[i] > rs[i + 1] + 1) {
            rs[i] = rs[i + 1] + 1;
            continue;
        }

        rs[i] = min(rs[i + 1], A[i] - 1);
    }

    // cerr << ls << endl;
    // cerr << rs << endl;

    int result{1};
    for (int i = 0; i < n; ++i) {
        result = max(result, min(ls[i], rs[i]) + 1);
    }
    cout << result << '\n';
    return 0;
}
