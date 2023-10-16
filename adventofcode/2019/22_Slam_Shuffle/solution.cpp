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

constexpr ll modmul(const ll x, const ll y) {
    return llof((i128of(x) * y) % i128of(mod));
}

constexpr ll modpow(ll b, ll e) {
    ll ans = 1;
    for (; e; b = modmul(b, b), e /= 2)
        if (e & 1) ans = modmul(ans, b);
    return ans;
}

constexpr ll modinv(const ll x) { return modpow(x, DeckSize - 2); }
}; // namespace kactl

ll source_index(const Op &op, const ll x) {
    const auto unrotated = [&](const ll k, const ll i) -> ll {
        if (i < DeckSize - k) {
            return k + i;
        } else {
            return i - (DeckSize - k);
        }
    };

    return visit(overloaded{[&]([[maybe_unused]] const Reverse &rev) -> ll {
                                return DeckSize - 1 - x;
                            },
                            [&](const Rotate &rot) -> ll {
                                if (rot.k > 0) {
                                    return unrotated(rot.k, x);
                                } else {
                                    assert(rot.k < 0);
                                    return unrotated(DeckSize + rot.k, x);
                                }
                            },
                            [&](const Skip &skp) -> ll {
                                assert(skp.k > 0);
                                return kactl::modmul(x, kactl::modinv(skp.k));
                            }},
                 op);
}

static constexpr ll ShufflesNum = 101741582076661LL;
static constexpr ll X = 2020;

ll source_index(const vector<Op> &ops, ll x) {
    for (const auto &op : ops | views::reverse) x = source_index(op, x);
    return x;
}

ll solve(const vector<Op> &ops) {
    const auto b = source_index(ops, 0);
    const auto a = (source_index(ops, 1) - b + DeckSize) % DeckSize;
    assert(a != 1LL);

    const auto An = kactl::modpow(a, ShufflesNum);
    const auto q = (1 - a + DeckSize) % DeckSize;
    const auto p = (1 - An + DeckSize) % DeckSize;
    const auto Sn = kactl::modmul(b, kactl::modmul(p, kactl::modinv(q)));

    return (kactl::modmul(An, X) + Sn) % DeckSize;
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

    cout << solve(ops) << '\n';
    return 0;
}
