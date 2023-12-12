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
        const auto al = arrangements_count(patterns[i] + "?", digests[i]);
        const auto ar = arrangements_count("?" + patterns[i], digests[i]);

        const auto cur = [&]() -> ll {
            if (al == a && ar == a) return ipow(a, 5);
            if (al != a && ar == a) return ipow(al, 4) * a;
            if (al == a && ar != a) return a * ipow(ar, 4);
            return 0;
        }();

        for (int bits = 0; bits < (1 << 4); ++bits) {
            const ll lefts = __builtin_popcount(bits);
            const ll rights = 4 - lefts;

            // ll x = a;
            // for (int k = 1; k <= lefts; ++k) x *= al;
            // for (int k = 1; k <= rights; ++k) x *= ar;
            // cur += x;
        }
        cerr << " a:" << a << " al:" << al << " ar:" << ar << " cur:" << cur
             << endl;
    }
    cout << result << '\n';
    return 0;
}
