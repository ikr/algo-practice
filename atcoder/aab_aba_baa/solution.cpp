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

ll factorial(const ll x) {
    assert(x >= 0);
    if (x <= 1) return 1;

    ll ans = 2;
    for (ll i = 3; i <= x; ++i) {
        ans *= i;
    }
    assert(ans > 0LL);
    return ans;
}

ll product_of_range(const ll a, const ll b) {
    ll ans = 1;
    for (ll x = a; x <= b; ++x) ans *= x;
    assert(ans > 0LL);
    return ans;
}

ll combinations(const ll n, const ll k) {
    assert(k <= n);
    const ll r = n - k;
    return r < k ? product_of_range(k + 1, n) / factorial(r)
                 : product_of_range(r + 1, n) / factorial(k);
}

string kth_element(const int a, const int b, const ll k) {
    for (int i = 1; i <= a; ++i) {
        cerr << combinations(b + i - 1, i) << endl;
    }

    return "";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    // string xs{"000111"};
    // do {
    //     cout << xs << '\n';
    // } while (next_permutation(begin(xs), end(xs)));

    int a, b;
    cin >> a >> b;

    ll k;
    cin >> k;
    --k;

    cout << kth_element(a, b, k) << '\n';
    return 0;
}
