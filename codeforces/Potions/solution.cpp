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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vvll reverse_sorted_prefixes_by_length(const vll &xs) {
    vvll ans(sz(xs) + 1);
    vll curr;
    curr.reserve(sz(xs));

    for (int length = 1; length <= sz(xs); ++length) {
        curr.insert(upper_bound(cbegin(curr), cend(curr), xs[length - 1]),
                    xs[length - 1]);

        ans[length] = vll(crbegin(curr), crend(curr));
    }

    return ans;
}

vvll reverse_sorted_prefix_sums_by_length(const vvll &rsp) {
    vvll ans = rsp;
    for (auto &prefix : ans) {
        partial_sum(cbegin(prefix), cend(prefix), begin(prefix));
    }
    return ans;
}

int max_drinks(const vll &xs) {
    const auto rsps = reverse_sorted_prefix_sums_by_length(
        reverse_sorted_prefixes_by_length(xs));

    const auto health = [&rsps](const int at_index,
                                const int potions_drunk) -> ll {
        return potions_drunk ? rsps[at_index + 1][potions_drunk - 1] : 0;
    };

    int ans = 0;

    for (int i = 0; i < sz(xs); ++i) {
        for (int p = 0; p <= i + 1; ++p) {
            cerr << "i:" << i << " p:" << p << " h:" << health(i, p) << endl;

            if (health(i, p) >= 0) ans = max(ans, p);
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vll xs(n);
    for (auto &x : xs) cin >> x;

    cout << max_drinks(xs) << '\n';
    return 0;
}
