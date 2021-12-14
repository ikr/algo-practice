#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

void line_break() {
    string x;
    getline(cin, x);
}

static constexpr int AZ = 26;

struct State final {
    vector<ll> char_freqs;
    array<array<ll, AZ>, AZ> pair_freqs;

    State() : char_freqs(AZ, 0), pair_freqs{} {
        for (auto a = 0; a < AZ; ++a) {
            for (auto b = 0; b < AZ; ++b) {
                assert(pair_freqs[a][b] == 0);
            }
        }
    }
};

constexpr int ctoi(const char x) { return inof(x) - inof('A'); }

State initial_state(const string &xs) {
    State st;

    for (const auto x : xs) ++st.char_freqs[ctoi(x)];

    for (int i = 1; i < sz(xs); ++i) {
        ++st.pair_freqs[ctoi(xs[i - 1])][ctoi(xs[i])];
    }

    return st;
}

using Rule = tuple<char, char, char>;

State evolve(const vector<Rule> &rules, const State &st) {
    State st_ = st;

    for (const auto [aa, bb, cc] : rules) {
        const auto a = ctoi(aa);
        const auto b = ctoi(bb);
        const auto c = ctoi(cc);

        if (!st.pair_freqs[a][b]) continue;

        st_.pair_freqs[a][b] -= st.pair_freqs[a][b];
        st_.pair_freqs[a][c] += st.pair_freqs[a][b];
        st_.pair_freqs[c][b] += st.pair_freqs[a][b];
        st_.char_freqs[c] += st.pair_freqs[a][b];
    }

    return st_;
}

int main() {
    string xs;
    cin >> xs;
    line_break();
    line_break();

    vector<Rule> rules;

    for (string line; getline(cin, line);) {
        const auto parts = split(" -> ", line);
        rules.emplace_back(parts[0][0], parts[0][1], parts[1][0]);
    }

    auto st = initial_state(xs);

    for (int i = 0; i < 40; ++i) {
        st = evolve(rules, st);
    }

    auto fs = st.char_freqs;
    sort(begin(fs), end(fs));
    fs.erase(remove(begin(fs), end(fs), 0), end(fs));
    cout << (fs.back() - fs[0]) << '\n';
    return 0;
}
