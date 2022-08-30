#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

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

ll value_of_line(const string &xs) {
    const auto n = sz(xs);
    ll result{};

    for (int i = 0; i < n; ++i) {
        if (xs[i] == 'L') {
            result += i;
        } else {
            assert(xs[i] == 'R');
            result += n - i - 1;
        }
    }

    return result;
}

vector<ll> max_line_values(const string &xs) {
    const auto n = sz(xs);
    vector<ll> wins;
    wins.reserve(n);

    for (int i = 0; i < n; ++i) {
        const auto cur = xs[i] == 'L' ? i : (n - i - 1);
        const auto pot = xs[i] == 'L' ? (n - i - 1) : i;

        if (pot > cur) wins.push_back(pot - cur);
    }

    while (sz(wins) < n) wins.push_back(0);
    sort(rbegin(wins), rend(wins));

    vector<ll> ss(n);
    partial_sum(cbegin(wins), cend(wins), begin(ss));

    vector<ll> result(n, value_of_line(xs));
    for (int i = 0; i < n; ++i) {
        result[i] += ss[i];
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;

        assert(sz(xs) == n);
        cout << max_line_values(xs) << '\n';
    }

    return 0;
}
