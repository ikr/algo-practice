#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

namespace kactl {
#define rep(i, a, b) for (int i = a; i < (b); ++i)

using vi = vector<int>;
using pii = pair<int, int>;

static constexpr int LIM = 1e7;
static constexpr int S = 3163, R = LIM / 2;

static bitset<LIM> isPrime;
vi eratosthenes() {
    vi pr = {2}, sieve(S + 1);
    pr.reserve(int(LIM / log(LIM) * 1.1));
    vector<pii> cp;
    for (int i = 3; i <= S; i += 2)
        if (!sieve[i]) {
            cp.push_back({i, i * i / 2});
            for (int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
        }
    for (int L = 1; L <= R; L += S) {
        array<bool, S> block{};
        for (auto &[p, idx] : cp)
            for (int i = idx; i < S + L; idx = (i += p)) block[i - L] = 1;
        rep(i, 0, min(S, R - L)) if (!block[i]) pr.push_back((L + i) * 2 + 1);
    }
    for (int i : pr) isPrime[i] = 1;
    return pr;
}
} // namespace kactl

vector<ll> precompute_primes() {
    const auto src = kactl::eratosthenes();
    vector<ll> ans(sz(src));
    copy(cbegin(src), cend(src), begin(ans));
    assert(is_sorted(begin(ans), end(ans)));
    return ans;
}

using lll = __int128_t;

int num_nums(const lll N) {
    const auto ps = precompute_primes();
    int ans{};

    for (int i = 0; i < sz(ps) - 2; ++i) {
        const lll a = ps[i];
        if (a * a > N) break;

        for (int j = i + 1; j < sz(ps) - 1; ++j) {
            const lll b = ps[j];
            if (a * a * b > N) break;

            for (int k = j + 1; k < sz(ps); ++k) {
                const lll c = ps[k];
                if (a * a * b * c * c > N) break;
                ++ans;
            }
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N;
    cin >> N;

    cout << num_nums(N) << '\n';
    return 0;
}
