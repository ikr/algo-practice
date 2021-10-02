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

template <typename T> vi digits_reversed(T n) {
    vi ans;

    while (n) {
        ans.push_back(n % 10);
        n /= 10;
    }

    return ans;
}

template <typename T> T number(const vector<int> &ds) {
    if (ds.empty()) return 0;

    T ans = 0;
    T mul = 1;
    for (auto it = ds.crbegin(); it != ds.crend(); ++it) {
        ans += (*it) * mul;
        mul *= static_cast<T>(10);
    }
    return ans;
}

ll max_prod(const int n) {
    auto ds = digits_reversed(n);
    sort(begin(ds), end(ds));

    ll ans = 0;

    do {
        for (int i = 1; i < sz(ds); ++i) {
            vi xs(cbegin(ds), cbegin(ds) + i);
            vi ys(cbegin(ds) + i, cend(ds));

            ans = max(ans, number<ll>(xs) * number<ll>(ys));
        }
    } while (next_permutation(begin(ds), end(ds)));

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;
    cout << max_prod(n) << '\n';
    return 0;
}
