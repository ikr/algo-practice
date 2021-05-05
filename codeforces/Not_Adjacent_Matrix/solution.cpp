#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

vvi construct_matrix(const int n) {
    if (n == 1) return {{1}};
    if (n == 2) return {};

    deque<int> odds;
    deque<int> evens;

    for (int i = 1; i <= n * n; ++i) {
        if (i % 2) {
            odds.push_back(i);
        } else {
            evens.push_back(i);
        }
    }

    vvi ans(n, vi(n, 0));
    for (auto &row : ans) {
        for (auto &cell : row) {
            if (odds.empty()) {
                cell = evens.front();
                evens.pop_front();
            } else {
                cell = odds.front();
                odds.pop_front();
            }
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        const auto ans = construct_matrix(n);
        if (ans.empty()) {
            cout << "-1\n";
        } else {
            cout << ans;
        }
    }

    return 0;
}
