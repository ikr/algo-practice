#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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

vi divisors(const int x) {
    vi ans;

    for (int i = 1; llof(i) * i <= llof(x); ++i) {
        if (x % i) continue;
        ans.push_back(i);

        const int q = x / i;
        if (q != i) ans.push_back(q);
    }

    return ans;
}

int min_ops(const string &a, const int total_ones, const int d) {
    vi mf(d, 0);

    for (int i = 0; i < sz(a); ++i) {
        if (a[i] == '0') continue;
        ++mf[i % d];
    }

    const auto it = max_element(cbegin(mf), cend(mf));
    assert(it != cend(mf));
    assert(*it > 0);

    const auto target = sz(a) / d;
    assert(target >= *it);

    const auto zeros_to_flip = target - *it;
    const auto ones_to_flip = total_ones - *it;
    return zeros_to_flip + ones_to_flip;
}

int min_ops(const string &a) {
    const int total_ones = inof(count(cbegin(a), cend(a), '1'));
    if (!total_ones) return 1;

    int ans = INT_MAX;

    for (const auto d : divisors(sz(a))) {
        ans = min(ans, min_ops(a, total_ones, d));
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

        string a(n, ' ');
        cin >> a;

        cout << min_ops(a) << '\n';
    }

    return 0;
}
