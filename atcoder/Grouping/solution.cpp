#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll group_score(const vvi &compat, const int bits_group) {
    const int n = sz(compat);
    ll ans = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            const bool one = (1 << i) & bits_group;
            const bool two = (1 << j) & bits_group;
            if (one && two) ans += compat[i][j];
        }
    }

    return ans;
}

vll group_scores(const vvi &compat) {
    const int n = sz(compat);
    vll ans(1 << n, 0);

    for (int bits = 1; bits < (1 << n); ++bits) {
        ans[bits] = group_score(compat, bits);
    }

    return ans;
}

vvi gather_free_bits(const int n) {
    vvi ans((1 << n));
    for (int taken = 0; taken < (1 << n); ++taken) {
        vi free_bits;
        for (int i = 0; i < n; ++i) {
            if ((1 << i) & taken) continue;
            free_bits.push_back(i);
        }

        for (int i = 1; i < (1 << sz(free_bits)); ++i) {
            int bits = 0;
            for (int j = 0; j < sz(free_bits); ++j) {
                if ((1 << j) & i) {
                    bits |= (1 << free_bits[j]);
                }
            }

            ans[taken].push_back(bits);
        }
    }
    return ans;
}

ll max_total_score(const vvi &compat) {
    const auto n = sz(compat);
    const auto score = group_scores(compat);
    const auto fb = gather_free_bits(n);
    vll memo(1 << n, -1LL);

    function<ll(int, int)> recur;
    recur = [&](const int bits_taken, const int bits_taking) -> ll {
        assert(!(bits_taken & bits_taking));
        if (memo[bits_taken | bits_taking] != -1LL) {
            return memo[bits_taken | bits_taking];
        }

        ll ans = score[bits_taking];
        for (const auto bits : fb[bits_taken | bits_taking]) {
            ans = max(ans, score[bits_taking] +
                               recur(bits_taken | bits_taking, bits));
        }

        memo[bits_taken | bits_taking] = ans;
        return ans;
    };

    ll ans = 0;
    for (int bits = 1; bits < (1 << n); ++bits) {
        ans = max(ans, recur(0, bits));
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vvi compat(n, vi(n, 0));
    for (auto &row : compat) {
        for (auto &x : row) {
            cin >> x;
        }
    }

    cout << max_total_score(compat) << '\n';
    return 0;
}
