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

vi days_by_players_count_shifted(const vector<pii> &ps) {
    map<int, int> incs;
    map<int, int> decs;
    set<int> ms;

    for (const auto [a, b] : ps) {
        ms.insert(a);
        ms.insert(a + b);

        ++incs[a];
        ++decs[a + b];
    }

    vi ans(sz(ps), 0);

    int curr = 0;
    for (const auto m : ms) {
        curr += incs[m];
        curr -= decs[m];

        assert(curr >= 0);
        if (curr) ++ans[curr - 1];
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    vector<pii> ps(n);
    for (auto &[a, b] : ps) cin >> a >> b;

    cout << days_by_players_count_shifted(ps) << '\n';
    return 0;
}
