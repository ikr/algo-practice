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

vll shortest_interesting_array(const ll C) {
    if (!C) return {1, 1};

    vi first_ones;
    vi first_zeroes;

    bitset<62> bits(static_cast<unsigned long long>(C));
    for (int i = 60; i >= 0; --i) {
        if (bits[i] && !bits[i + 1]) {
            first_ones.push_back(i);
        } else if (!bits[i] && bits[i + 1]) {
            first_zeroes.push_back(i);
        }
    }

    vll ans;

    for (const auto i : first_ones) {
        ans.push_back((1LL << (i + 1)) - 1LL);
    }

    for (const auto i : first_zeroes) {
        ans.push_back((1LL << (i + 1)) - 1LL);
    }

    sort(begin(ans), end(ans));
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        ll C;
        cin >> C;

        const auto ans = shortest_interesting_array(C);
        cout << sz(ans) << '\n' << ans << '\n';
    }

    return 0;
}
