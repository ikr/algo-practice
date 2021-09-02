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

bool can_win(vi &xs, const int K, const int L) {
    if (sz(xs) == 1) return true;
    xs.back() = max(xs.back(), xs.back() + K * (L - 1));

    vi idx(sz(xs));
    iota(begin(idx), end(idx), 0);
    sort(begin(idx), end(idx),
         [&](const int i, const int j) { return xs[i] > xs[j]; });

    return (idx[0] == sz(xs) - 1) && (xs[idx[1]] < xs[idx[0]]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int N, K, L;
        cin >> N >> K >> L;

        vi xs(N);
        for (auto &x : xs) cin >> x;

        cout << (can_win(xs, K, L) ? "Yes" : "No") << '\n';
    }

    return 0;
}
