#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> var_bit_indices(const string &xs) {
    vector<int> ans;
    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == '?') ans.push_back(i);
    }
    return ans;
}

ll instantiate(string xs, const vector<int> &vs, const ll bitmask) {
    const auto n = sz(xs);

    for (const auto i : vs) {
        if ((1LL << (n - 1 - i)) & bitmask) {
            xs[i] = '1';
        } else {
            xs[i] = '0';
        }
    }

    bitset<61> ans{xs};
    return llof(ans.to_ullong());
}

ll top_val(const string &xs, const ll N) {
    const auto vs = var_bit_indices(xs);
    if (instantiate(xs, vs, 0LL) > N) return -1;

    ll lo = 0LL;
    ll hi = (1LL << 62) - 1LL;
    if (instantiate(xs, vs, hi) <= N) return instantiate(xs, vs, hi);

    while (lo + 1 < hi) {
        const auto mid = lo + (hi - lo) / 2LL;
        const auto y = instantiate(xs, vs, mid);

        if (y <= N) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return instantiate(xs, vs, lo);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    ll N;
    cin >> N;

    cout << top_val(xs, N) << '\n';
    return 0;
}
