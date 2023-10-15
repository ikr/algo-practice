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

ll source_index_for_one_complete_shuffle(const vector<Op> &ops, ll m) {
    for (const auto &op : ops | views::reverse) {
        m = source_index(op, m);
    }

    return m;
}

template <typename T>
bool is_at(const vector<T> &haystack, const vector<T> &needle, const int i) {
    for (int j = 0; j < sz(needle); ++j) {
        if (haystack[i + j] != needle[j]) return false;
    }

    return true;
}

template <typename T> int tail_period(const vector<T> &xs) {
    const auto marker_size = 4;
    const vector marker(cend(xs) - marker_size, cend(xs));
    assert(is_at(xs, marker, sz(xs) - marker_size));

    for (int i = sz(xs) - marker_size - 1; i >= 0; --i) {
        if (is_at(xs, marker, i)) {
            return sz(xs) - marker_size - i;
        }
    }

    return -1;
}

void explore(const vector<Op> &ops, const ll m) {
    vector<ll> xs;
    auto cur = m;
    for (int i = 1; i <= 100'000; ++i) {
        const auto cur_ = source_index_for_one_complete_shuffle(ops, cur);
        xs.push_back((cur_ - cur + DeckSize) % DeckSize);
        cur = cur_;
    }
    cerr << "Period: " << tail_period(xs) << endl;
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

    cout << source_index_for_one_complete_shuffle(ops, 2020) << '\n';
    explore(ops, 2020);
    return 0;
}
