#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

vector<int> parse_ints(const string &src) {
    const auto tokens = split(",", src);
    vector<int> ans(sz(tokens));
    transform(cbegin(tokens), cend(tokens), begin(ans),
              [](const string &s) { return stoi(s); });
    return ans;
}

vector<int> wildcard_indices(const string &s) {
    vector<int> ans;
    for (int i = 0; i < sz(s); ++i) {
        if (s[i] == '?') ans.push_back(i);
    }
    return ans;
}

vector<pair<char, int>> run_length_encode(const string &xs) {
    vector<pair<char, int>> ans{{xs[0], 1}};
    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] == ans.back().first) {
            ++(ans.back().second);
        } else {
            ans.emplace_back(xs[i], 1);
        }
    }
    return ans;
}

bool confirm_match(const vector<int> &digest, const string &src) {
    const auto src_rle = run_length_encode(src);
    vector<int> candidate;
    for (const auto &[c, n] : src_rle) {
        if (c == '#') {
            candidate.push_back(n);
        }
    }
    return digest == candidate;
}

int arrangements_count(const string &pattern, const vector<int> &digest) {
    const auto wi = wildcard_indices(pattern);
    int result{};
    for (int bits = 0; bits < (1 << sz(wi)); ++bits) {
        string candidate = pattern;
        for (int i = 0; i < sz(wi); ++i) {
            if (bits & (1 << i)) {
                candidate[wi[i]] = '#';
            } else {
                candidate[wi[i]] = '.';
            }
        }

        if (confirm_match(digest, candidate)) ++result;
    }
    return result;
}

constexpr ll ipow(const ll base, const int exp) {
    return exp == 0 ? 1 : base * ipow(base, exp - 1);
}

bool head_fixed(const string &pattern, const vector<int> &digest) {
    const auto rle = run_length_encode(pattern);
    return rle[0].first == '#' && rle[0].second == digest[0];
}

bool tail_fixed(const string &pattern, const vector<int> &digest) {
    const auto rle = run_length_encode(pattern);
    return rle.back().first == '#' && rle.back().second == digest.back();
}

int main() {
    vector<string> patterns;
    vector<vector<int>> digests;

    for (string line; getline(cin, line);) {
        const auto parts = split(" ", line);
        patterns.push_back(parts[0]);
        digests.push_back(parse_ints(parts[1]));
    }

    ll result{};
    for (int i = 0; i < sz(patterns); ++i) {
        const auto a = arrangements_count(patterns[i], digests[i]);
        const auto asuff = arrangements_count(patterns[i] + "?", digests[i]);
        const auto apref = arrangements_count("?" + patterns[i], digests[i]);

        const auto cur = [&]() -> ll {
            if (head_fixed(patterns[i], digests[i]) ||
                tail_fixed(patterns[i], digests[i])) {
                return ipow(a, 5);
            }
            if (asuff == a && apref == a) return ipow(a, 5);
            if (asuff != a && apref == a) return ipow(asuff, 4) * a;
            if (asuff == a && apref != a) return a * ipow(apref, 4);
            assert(asuff != a && apref != a);

            ll ans{};
            for (int bits = 0; bits < (1 << 4); ++bits) {
                const ll suffs = __builtin_popcount(bits);
                const ll prefs = 4 - suffs;

                ll x = a;
                for (int k = 1; k <= suffs; ++k) x *= asuff;
                for (int k = 1; k <= prefs; ++k) x *= apref;
                ans += x;
            }
            return ans;
        }();

        cerr << " a:" << a << " al:" << asuff << " ar:" << apref
             << " cur:" << cur << endl;
        result += cur;
    }
    cout << result << '\n';
    return 0;
}
