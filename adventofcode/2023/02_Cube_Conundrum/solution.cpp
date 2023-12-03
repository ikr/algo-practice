#include <bits/stdc++.h>
using namespace std;

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

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

int main() {
    vector<vector<map<string, int>>> games;

    for (string line; getline(cin, line);) {
        const auto parts = split(": ", line);
        games.push_back(parse_subs(parts[1]));
    }

    cout << transform_reduce(cbegin(games), cend(games), 0, plus<>{},
                             [](const auto &game) {
                                 auto inv = min_possible_inventory(game);
                                 return inv["red"] * inv["green"] * inv["blue"];
                             })
         << '\n';
    return 0;
}
