#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr i128 i128of(const T x) {
    return static_cast<i128>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

struct Reverse final {};

struct Rotate final {
    int k;
};

struct Skip final {
    int k;
};

using Op = variant<Reverse, Rotate, Skip>;
template <class... Ts> struct overloaded : Ts... {
    using Ts::operator()...;
};

static constexpr ll DeckSize = 119315717514047LL;

// https://github.com/kth-competitive-programming/kactl
namespace kactl {
static constexpr ll mod = DeckSize;
ll modpow(ll b, ll e) {
    ll ans = 1;
    for (; e; b = llof(i128of(b) * b % i128of(mod)), e /= 2)
        if (e & 1) ans = llof((i128of(ans) * b) % i128of(mod));
    return ans;
}
}; // namespace kactl

ll modinv(const ll x) { return kactl::modpow(x, DeckSize - 2); }

ll source_index(const Op &op, const ll m) {
    const auto unrotated = [&](const ll k, const ll i) -> ll {
        if (i < DeckSize - k) {
            return k + i;
        } else {
            return i - (DeckSize - k);
        }
    };

    return visit(overloaded{[&]([[maybe_unused]] const Reverse &rev) -> ll {
                                return DeckSize - 1 - m;
                            },
                            [&](const Rotate &rot) -> ll {
                                if (rot.k > 0) {
                                    return unrotated(rot.k, m);
                                } else {
                                    assert(rot.k < 0);
                                    return unrotated(DeckSize + rot.k, m);
                                }
                            },
                            [&](const Skip &skp) -> ll {
                                assert(skp.k > 0);
                                return llof((i128of(m) * modinv(skp.k)) %
                                            i128of(DeckSize));
                            }},
                 op);
}

ll source_index(const vector<Op> &ops, ll m) {
    for (const auto &op : ops | views::reverse) {
        m = source_index(op, m);
    }

    return m;
}

int main() {
    vector<Op> ops;

    for (string line; getline(cin, line);) {
        if (empty(line)) continue;

        if (line == "deal into new stack") {
            ops.push_back(Reverse{});
        } else if (line.starts_with("cut")) {
            const auto k = stoi(line.substr(4));
            ops.push_back(Rotate{k});
        } else if (line.starts_with("deal with increment")) {
            const auto k = stoi(line.substr(20));
            ops.push_back(Skip{k});
        } else {
            assert(false && "Invalid operation description");
        }
    }

    cout << source_index(ops, 2020) << '\n';
    return 0;
}
