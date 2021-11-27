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

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> vector<T> digits_reversed(T n) {
    vector<T> ans;

    while (n) {
        ans.push_back(n % static_cast<T>(10));
        n /= static_cast<T>(10);
    }

    return ans;
}

template <typename T> vi digits(T n) {
    vi ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

bool is_hard(const ll a, const ll b) {
    const auto xs = digits_reversed(a);
    const auto ys = digits_reversed(b);

    for (int i = 0; i < min(sz(xs), sz(ys)); ++i) {
        if (xs[i] + ys[i] > 9) return true;
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll a, b;
    cin >> a >> b;

    cout << (is_hard(a, b) ? "Hard" : "Easy") << '\n';
    return 0;
}
