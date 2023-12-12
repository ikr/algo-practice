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
        if (i + d > n) return false;
        return all_of(cbegin(pattern) + i, cbegin(pattern) + i + d,
                      [](const char c) { return c == '#' || c == '?'; }) &&
               (i + d == n || pattern[i + d] == '.' || pattern[i + d] == '?');
    };

    const auto possible_shifts_starting_at = [&](const int i,
                                                 const int d) -> int {
        assert(is_match_possible(i, d));
        int result{};
        while (is_match_possible(i + result + 1, d)) ++result;
        return result;
    };

    vector<vector<ll>> memo(2 * n, vector(2 * m, -1LL));

    const auto recur = [&](const auto self, int i, const int j) -> ll {
        if (memo[i][j] != -1) return memo[i][j];
        return memo[i][j] = [&]() -> ll {
            while (i < n && pattern[i] == '.') ++i;
            if (i >= n && j >= m) return 1LL;
            if (i >= n || j >= m) return 0LL;

            while (i < n && !is_match_possible(i, digest[j])) ++i;
            if (i == n) return 0LL;

            const auto ss = possible_shifts_starting_at(i, digest[j]);
            ll ans{};
            for (int s = 0; s <= ss; ++s) {
                ans += self(self, i + s + digest[j] + 1, j + 1);
            }
            return ans;
        }();
    };

    const auto result = recur(recur, 0, 0);
    cerr << memo << endl;
    return result;
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
        const auto cur = arrangements_count(patterns[i], digests[i]);
        cerr << "cur:" << cur << endl;
        result += cur;
    }
    cout << result << '\n';
    return 0;
}
