#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

int main() {
    vector<int> wins;
    for (string line; getline(cin, line);) {
        const auto a = split(":\\s+", line);
        const auto b = split("\\s+\\|\\s+", a[1]);
        const auto left = split("\\s+", b[0]);
        const auto right = split("\\s+", b[1]);

        vector<int> winning(sz(left));
        ranges::transform(left, begin(winning),
                          [](const string &s) { return stoi(s); });

        vector<int> posession(sz(right));
        ranges::transform(right, begin(posession),
                          [](const string &s) { return stoi(s); });

        const auto winning_set = set(cbegin(winning), cend(winning));
        int k{};
        for (const auto x : posession) {
            if (winning_set.contains(x)) ++k;
        }
        wins.push_back(k);
    }

    vector<int> mul(sz(wins), 1);
    for (int i = 0; i < sz(wins); ++i) {
        for (int j = i + 1; j <= i + wins[i]; ++j) {
            mul[j] += mul[i];
        }
    }

    cout << accumulate(cbegin(mul), cend(mul), 0) << '\n';
    return 0;
}
