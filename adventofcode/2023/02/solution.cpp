#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> static_re_matches(const string &pattern_str,
                                 const string &input) {
    static const regex pattern{pattern_str};
    smatch m;
    regex_match(input, m, pattern);
    assert(!empty(m));

    vector<string> result(size(m) - 1);
    transform(cbegin(m) + 1, cend(m), begin(result),
              [](const auto &x) { return x.str(); });
    return result;
}

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

static const string LinePattern = R"(^Game \d+: (.+)$)";

map<string, int> parse_sub(const string &s) {
    map<string, int> result;

    const auto tokens = split(", ", s);
    for (const auto &t : tokens) {
        const auto kv = split(" ", t);
        result[kv[1]] = stoi(kv[0]);
    }

    return result;
}

vector<map<string, int>> parse_subs(const string &s) {
    vector<map<string, int>> result;

    const auto tokens = split("; ", s);
    for (const auto &t : tokens) {
        result.push_back(parse_sub(t));
    }

    return result;
}

map<string, int> take_maximum(map<string, int> xs, const map<string, int> &ys) {
    for (const auto &[k, v] : ys) {
        xs[k] = max(xs[k], v);
    }
    return xs;
}

map<string, int> min_possible_inventory(const vector<map<string, int>> &game) {
    map<string, int> result;
    for (const auto &sub : game) {
        result = take_maximum(result, sub);
    }
    return result;
}

using ll = long long;

int main() {
    vector<vector<map<string, int>>> games;

    for (string line; getline(cin, line);) {
        const auto parts = static_re_matches(LinePattern, line);
        games.push_back(parse_subs(parts[0]));
    }

    ll result{};
    for (int i = 0; i < sz(games); ++i) {
        auto inv = min_possible_inventory(games[i]);
        ll cur = inv["red"];
        cur *= inv["green"];
        cur *= inv["blue"];
        result += cur;
    }
    cout << result << '\n';
    return 0;
}
