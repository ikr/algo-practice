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

ll brute_force_card_at_position_m(const vector<Op> &ops, const ll m) {
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

    const auto result = brute_force_card_at_position_m(ops, 6850);
    cout << result << '\n';
    return 0;
}
