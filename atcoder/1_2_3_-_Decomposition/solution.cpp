#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi digits_reversed(ll n) {
    vi ans;

    while (n) {
        ans.push_back(inof(n % 10LL));
        n /= 10;
    }

    return ans;
}

static constexpr int K_MAX = 5;

int min_k(const ll n) {
    const auto xs = digits_reversed(n);

    // ok[i][k][c] is true iﬀ it is possible to produce a carry c at digit i
    // after summing up k 123-numbers

    vector<vector<vector<bool>>> ok(
        sz(xs), vector(K_MAX + 1, vector(K_MAX + 1, false)));

    for (int k = 1; k <= K_MAX; ++k) {
        for (int v = k; v <= 3 * k; ++v) {
            if (v % 10 == xs[0]) {
                ok[0][k][v / 10] = true;
            }
        }
    }

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;

        cout << min_k(n) << '\n';
    }

    return 0;
}
