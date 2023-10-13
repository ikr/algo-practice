#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

static constexpr ll DeckSize = 10007;

ll brute_force_card_at_m(const vector<Op> &ops, const ll m) {
    assert(DeckSize < 100'000'000);

    const auto skipped = [](const vector<int> &xs, const int k) -> vector<int> {
        vector<int> ans(sz(xs));
        for (int i = 0; i < sz(xs); ++i) {
            ans[(i * k) % sz(xs)] = xs[i];
        }
        return ans;
    };

    vector<int> xs(DeckSize);
    iota(begin(xs), end(xs), 0);

    for (const auto &op : ops) {
        visit(overloaded{[&]([[maybe_unused]] const Reverse &rev) {
                             ranges::reverse(xs);
                         },
                         [&](const Rotate &rot) {
                             if (rot.k > 0) {
                                 rotate(begin(xs), begin(xs) + rot.k, end(xs));
                             } else {
                                 assert(rot.k < 0);
                                 rotate(begin(xs), end(xs) + rot.k, end(xs));
                             }
                         },
                         [&](const Skip &skp) {
                             assert(skp.k > 0);
                             xs = skipped(xs, skp.k);
                         }},
              op);
    }

    return xs[m];
}

ll source_position(const Op &op, const ll m) {
    const auto unrotated = [&](const ll k, const ll i) -> {
        if (i < DeckSize - k) {
            return k + i;
        } else {
            return m - (DeckSize - k);
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
                                    return unrotated(DeckSize - rot.k, m);
                                }
                            },
                            [&](const Skip &skp) -> ll {
                                assert(skp.k > 0);
                                return -1;
                            }},
                 op);
}

ll card_at_m(const vector<Op> &ops, const ll m) { return -1; }

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

    const auto result = brute_force_card_at_m(ops, 6850);
    cout << result << '\n';
    return 0;
}
