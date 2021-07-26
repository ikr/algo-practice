#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

vector<bool> sieve(const int n) {
    vector<bool> ans(n + 1, true);
    ans[0] = false;
    ans[1] = false;

    for (int i = 2; i <= n; ++i) {
        if (!ans[i]) continue;
        if (llof(i) * i > llof(n)) continue;
        for (int j = i * i; j <= n; j += i) ans[j] = false;
    }

    return ans;
}

vi primes(const vector<bool> &s) {
    vi ans;
    ans.reserve(sz(s) / 2);

    for (int i = 0; i < sz(s); ++i) {
        if (s[i]) ans.push_back(i);
    }

    return ans;
}

static constexpr int N_MAX = 10'000'000;

int components_num(const vi &ps, const int n) {
    const auto ps_num_up_to = [&ps](const int x) -> int {
        return inof(distance(cbegin(ps), upper_bound(cbegin(ps), cend(ps), x)));
    };

    const int all = ps_num_up_to(n);
    const int lo = ps_num_up_to(n / 2);
    return all - lo + (lo ? 1 : 0);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto ps = primes(sieve(N_MAX));

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << components_num(ps, n) << '\n';
    }

    return 0;
}
