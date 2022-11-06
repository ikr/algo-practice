#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

optional<vector<vector<int>>> gen_board(const int n, const int k) {
    if ((n * n) % k) return nullopt;
    if (k == 1) {
        if (n == 1) return vector<vector<int>>{{1}};
        return nullopt;
    }

    vector<vector<int>> result(n, vector(n, 0));

    for (int ro = 0; ro < n; ++ro) {
        for (int co = 0; co < n; ++co) {
            const int r = (ro * n + co) % k;
            result[ro][co] = r + 1;
        }
    }

    for (int ro = 1; ro < n; ++ro) {
        if (result[ro][0] == result[ro - 1][0]) {
            rotate(begin(result[ro]), next(begin(result[ro])), end(result[ro]));
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    const auto ans = gen_board(n, k);
    if (ans) {
        cout << "Yes\n" << (*ans);
    } else {
        cout << "No\n";
    }
    return 0;
}
