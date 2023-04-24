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

vector<int> super_permutation(const int n) { return {}; }

bool is_perm(const vector<int> &xs) {
    const auto n = sz(xs);
    const set<int> xss(cbegin(xs), cend(xs));
    return sz(xss) == n && *cbegin(xss) == 1 && *crbegin(xss) == n;
}

bool is_super(const vector<int> &xs) {
    const auto n = sz(xs);
    vector<int> ss(n);
    partial_sum(cbegin(xs), cend(xs), begin(ss),
                [n](const int a, const int b) { return (a + b) % n; });
    transform(begin(ss), end(ss), begin(ss),
              [n](const auto a) { return (a % n) + 1; });
    return is_perm(ss);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    assert(is_super({6, 5, 2, 3, 4, 1}));
    assert(is_super({2, 1}));
    assert(!is_super({1, 2}));
    assert(!is_super({2, 3, 1}));

    vector P{1, 2, 3, 4, 5, 6};
    do {
        if (is_super(P)) {
            cerr << "Ps: " << P << endl;
        }
    } while (next_permutation(begin(P), end(P)));

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        const auto ans = super_permutation(n);
        if (ans.empty()) {
            cout << "-1\n";
        } else {
            cout << ans << '\n';
        }
    }

    return 0;
}
