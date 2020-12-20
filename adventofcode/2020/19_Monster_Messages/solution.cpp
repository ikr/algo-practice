#include <bits/stdc++.h>
#include <variant>
using namespace std;
using vi = vector<int>;
using pvi = pair<vi, vi>;

template <class... Ts> struct overloaded final : Ts... {
    using Ts::operator()...;
};

template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template <typename Variant, typename... Matchers>
auto match(Variant &&variant, Matchers &&... matchers) {
    return visit(overloaded{forward<Matchers>(matchers)...},
                 forward<Variant>(variant));
}

vector<string> split(const regex &delim, const string &s) {
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), delim, -1),
                          sregex_token_iterator{});
}

string join(const vector<string> &tokens) {
    string ans;
    for (const auto &t : tokens) ans += t;
    return ans;
}

bool contains(const string &haystack, const string &needle) {
    return haystack.find(needle) != string ::npos;
}

using RuleSpec = variant<string, vi, pvi>;

struct Rule final {
    int id;
    RuleSpec spec;
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

int max_id(const vector<Rule> &rules) {
    int ans = -1;
    for (const auto &r : rules) ans = max(ans, r.id);
    return ans;
}

vector<RuleSpec> gather_rules_index(const vector<Rule> &rules) {
    vector<RuleSpec> ans(max_id(rules) + 1);
    for (const auto &r : rules) ans[r.id] = r.spec;
    return ans;
}

string extract_rule(const vector<RuleSpec> &idx, const int id) {
    if (id == 8) {
        return extract_rule(idx, 42) + "+";
    }

    if (id == 11) {
        const auto pref = extract_rule(idx, 42);
        const auto suff = extract_rule(idx, 31);
        return "(" + pref + "(?1)?" + suff + ")";
    }

    const auto extract_xs = [&idx](const vi &xs) {
        vector<string> ans(xs.size());
        transform(cbegin(xs), cend(xs), begin(ans),
                  [&idx](const int x) { return extract_rule(idx, x); });
        return join(ans);
    };

    return match(
        idx[id], [](const string &s) { return s; }, extract_xs,
        [&](const pvi &p) {
            const auto &[xs, ys] = p;
            return "(?:(?:" + extract_xs(xs) + ")|(?:" + extract_xs(ys) + "))";
        });
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

    const auto rules_idx = gather_rules_index(rules);
    /*const regex re{extract_rule(rules_idx, 0)};

    int ans = 0;
    for (const auto &m : messages_block) {
        if (regex_match(m, re)) ++ans;
    }
    cout << ans << '\n';*/

    cout << extract_rule(rules_idx, 0) << '\n';
    // And then: cat ./in1 | grep -P '^…$' | wc -l
    // as the std::regex doesn't seem to support the PCRE with recursion.
    return 0;
}
