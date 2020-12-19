#include <bits/stdc++.h>
#include <variant>
using namespace std;
using vi = vector<int>;
using pvi = pair<vi, vi>;

vector<string> split(const regex &delim, const string &s) {
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), delim, -1),
                          sregex_token_iterator{});
}

bool contains(const string &haystack, const string &needle) {
    return haystack.find(needle) != string ::npos;
}

struct Rule final {
    int id;
    variant<string, vi, pvi> spec;
};

vi parse_nums(const string &nums) {
    const auto tokens = split(regex(" "), nums);
    vi ans(tokens.size(), 0);
    transform(cbegin(tokens), cend(tokens), begin(ans),
              [](const auto &t) { return stoi(t); });
    return ans;
}

pair<string, string> head_split(const string &line) {
    const auto parts = split(regex(": "), line);
    return {parts[0], parts[1]};
}

Rule parse_rule(const string &line) {
    const auto [head, tail] = head_split(line);

    if (tail[0] == '"') {
        return {stoi(head), tail.substr(1, 1)};
    }

    if (contains(tail, " | ")) {
        const auto parts = split(regex(" \\| "), tail);
        return {stoi(head), pair{parse_nums(parts[0]), parse_nums(parts[1])}};
    }

    return {stoi(head), parse_nums(tail)};
}

int main() {
    vector<string> lines;

    for (string line; getline(cin, line);) {
        lines.push_back(line);
    }

    const auto mid = find(cbegin(lines), cend(lines), "");
    const vector<string> rules_block(cbegin(lines), mid);
    const vector<string> messages_block(next(mid), cend(lines));

    vector<Rule> rules(rules_block.size());
    transform(cbegin(rules_block), cend(rules_block), begin(rules), parse_rule);

    return 0;
}
