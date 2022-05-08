#include <algorithm>
#include <bitset>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const __uint128_t N_MAX = 1000000000000000000ULL;

// source
// https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/Eratosthenes.h
#define rep(i, a, b) for (int i = a; i < (b); ++i)
using vi = vector<int>;
const int MAX_PR = 170'000;
bitset<MAX_PR> isprime;
vi eratosthenesSieve(int lim) {
    isprime.set();
    isprime[0] = isprime[1] = 0;
    for (int i = 4; i < lim; i += 2) isprime[i] = 0;
    for (int i = 3; i * i < lim; i += 2)
        if (isprime[i])
            for (int j = i * i; j < lim; j += i * 2) isprime[j] = 0;
    vi pr;
    rep(i, 2, lim) if (isprime[i]) pr.push_back(i);
    return pr;
}

ll num_similar_within(const ll N) {
    vector<int> ps;
    for (int p = 2; p < MAX_PR; ++p) {
        if (isprime[p]) ps.push_back(p);
    }

    vector<ll> xs;
    for (int i = 0; i < sz(ps) - 1; ++i) {
        {
            __uint128_t y = ps[i];
            y *= ps[i + 1];
            if (y > N_MAX) continue;
        }

        for (int j = i + 1; j < sz(ps); ++j) {
            __uint128_t y = ps[i];
            y *= ps[j];
            if (y > N_MAX) continue;
            y *= ps[j];
            if (y > N_MAX) continue;
            y *= ps[j];
            if (y > N_MAX) continue;

            xs.push_back(llof(ps[i]) * llof(ps[j]) * llof(ps[j]) * llof(ps[j]));
        }
    }

    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));

    return inof(distance(cbegin(xs), upper_bound(cbegin(xs), cend(xs), N)));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    eratosthenesSieve(MAX_PR - 1);

    ll N;
    cin >> N;
    cout << num_similar_within(N) << endl;

    return 0;
}
