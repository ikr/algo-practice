#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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

ll arrangements_count(const string &pattern, const vector<int> &digest) {
    const auto n = sz(pattern);
    const auto m = sz(digest);

    const auto is_match_possible = [&](const int i, const int d) -> bool {
        const auto result = [&]() {
            if (i + d > n) return false;
            return all_of(cbegin(pattern) + i, cbegin(pattern) + i + d,
                          [](const char c) { return c == '#' || c == '?'; }) &&
                   (i + d == n || pattern[i + d] == '.' ||
                    pattern[i + d] == '?') &&
                   (i == 0 || pattern[i - 1] == '.' || pattern[i - 1] == '?');
        }();

        // cerr << "match = " << result << " for i:" << i << " d:" << d << endl;
        return result;
    };

    vector<vector<ll>> memo(n + 2, vector(m + 1, -1LL));

    const auto recur = [&](const auto self, const int i, const int j) -> ll {
        if (memo[i][j] != -1) return memo[i][j];
        return memo[i][j] = [&]() -> ll {
            if (i >= n && j >= m) return 1LL;
            if (j >= m) {
                if (pattern[i] == '#') return 0;
                return self(self, i + 1, j);
            }
            if (i >= n) return 0;

            if (is_match_possible(i, digest[j])) {
                const auto a = self(self, i + digest[j] + 1, j + 1);
                return pattern[i] == '#' ? a : (a + self(self, i + 1, j));
            } else {
                if (pattern[i] == '#') return 0;
                return self(self, i + 1, j);
            }
        }();
    };

    const auto result = recur(recur, 0, 0);
    cerr << memo << endl;
    return result;
}

namespace brute {
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
} // namespace brute

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
        const auto cur = arrangements_count(patterns[i], digests[i]);
        const auto org = brute::arrangements_count(patterns[i], digests[i]);
        if (cur != org) {
            cerr << "mismatch for " << patterns[i] << " " << digests[i] << endl;
            cerr << "cur: " << cur << endl;
            cerr << "org: " << org << endl;
            return 0;
        }
        cerr << "cur:" << cur << endl;
        result += cur;
    }
    cout << result << '\n';
    return 0;
}
