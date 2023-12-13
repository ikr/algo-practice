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
        auto p = patterns[i];
        for (int j = 1; j <= 4; ++j) p += "?" + patterns[i];

        vector<int> d = digests[i];
        for (int j = 1; j <= 4; ++j)
            d.insert(cend(d), cbegin(digests[i]), cend(digests[i]));

        result += arrangements_count(p, d);
    }
    cout << result << '\n';
    return 0;
}
