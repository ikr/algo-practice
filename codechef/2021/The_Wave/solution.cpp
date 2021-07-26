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

constexpr int mo_pow(const int exp) { return exp % 2 == 0 ? 1 : -1; }

int the_sign(const vi &a, const int x) {
    const auto it = lower_bound(cbegin(a), cend(a), x);

    if (it != cend(a)) {
        if (*it == x) return 0;

        return mo_pow(inof(distance(cbegin(a), it)));
    }

    return mo_pow(sz(a));
}

string interpret(const int sg) {
    if (sg == 0) return "0";
    return sg < 0 ? "NEGATIVE" : "POSITIVE";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n, q;
    cin >> n >> q;

    vi a(n);
    for (auto &x : a) cin >> x;

    sort(begin(a), end(a));

    while (q--) {
        int x;
        cin >> x;

        cout << interpret(the_sign(a, x)) << '\n';
    }

    return 0;
}
