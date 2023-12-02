#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
    return os;
}

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

bool is_possible(const map<string, int> &inventory,
                 const map<string, int> &sub) {
    return all_of(cbegin(sub), cend(sub), [&](const auto &kv) {
        const auto it = inventory.find(kv.first);
        return it != cend(inventory) && it->second >= kv.second;
    });
}

int main() {
    vector<vector<map<string, int>>> games;

    for (string line; getline(cin, line);) {
        const auto parts = static_re_matches(LinePattern, line);
        games.push_back(parse_subs(parts[0]));
    }

    const map<string, int> inventory{{"red", 12}, {"green", 13}, {"blue", 14}};

    int result{};
    for (int i = 0; i < sz(games); ++i) {
        const auto id = i + 1;
        if (all_of(cbegin(games[i]), cend(games[i]), [&](const auto &sub) {
                return is_possible(inventory, sub);
            })) {
            result += id;
        }
    }
    cout << result << '\n';
    return 0;
}
