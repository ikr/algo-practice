#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char chof(const int x) { return static_cast<char>(x); }

char most_frequent_char(const string &xs) {
    vector<int> fq(26, 0);
    for (const auto x : xs) ++fq[x - 'a'];

    const auto i = inof(max_element(cbegin(fq), cend(fq)) - cbegin(fq));
    return chof('a' + i);
}

int min_ops_of_2nd_type(const string &xs) {
    const auto n = sz(xs);
    const auto c0 = most_frequent_char(xs);
    return n - inof(count(cbegin(xs), cend(xs), c0));
}

int min_ops_forking(const string &xs, const int without_i) {
    const auto n = sz(xs);

    string ev;
    ev.reserve(n / 2);
    string od;
    od.reserve(n / 2);

    for (int i = 0; i < n; ++i) {
        if (i < without_i) {
            if (i % 2) {
                od.push_back(xs[i]);
            } else {
                ev.push_back(xs[i]);
            }
        } else if (i > without_i) {
            if (i % 2 == 0) {
                od.push_back(xs[i]);
            } else {
                ev.push_back(xs[i]);
            }
        }
    }

    return min_ops_of_2nd_type(ev) + min_ops_of_2nd_type(od) +
           (without_i == INT_MAX ? 0 : 1);
}

int min_ops(const string &xs) {
    const auto n = sz(xs);
    if (n % 2) {
        int result{INT_MAX};
        for (int i = 0; i < n; ++i) {
            result = min(result, min_ops_forking(xs, i));
        }
        return result;
    } else {
        return min_ops_forking(xs, INT_MAX);
    }
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

        cout << min_ops(xs) << '\n';
    }

    return 0;
}
