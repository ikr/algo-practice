#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
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

vector<string> re_matches(const string &pattern_str, const string &input) {
    const regex pattern{pattern_str};
    smatch m;
    regex_match(input, m, pattern);
    assert(!empty(m));

    vector<string> result(size(m) - 1);
    transform(cbegin(m) + 1, cend(m), begin(result),
              [](const auto &x) { return x.str(); });
    return result;
}

enum class Cat { x, m, a, s };
enum class Cmp { lt, gt, lte, gte };
using Dest = string;

struct Pred final {
    Cat cat;
    Cmp cmp;
    int val;
};

using Cond = pair<Pred, Dest>;

using Ruleset = pair<vector<Cond>, Dest>;
using Part = array<int, 4>;

static const Dest Accept{"A"};
static const Dest Reject{"R"};

constexpr Cmp opposite(const Cmp c) {
    switch (c) {
    case Cmp::lt:
        return Cmp::gte;
    case Cmp::gt:
        return Cmp::lte;
    case Cmp::lte:
        return Cmp::gt;
    default:
        assert(c == Cmp::gte);
        return Cmp::lt;
    }
}

constexpr Pred negate_pred(const Pred &p) {
    return Pred{p.cat, opposite(p.cmp), p.val};
}

Cat parse_cat(const char c) {
    switch (c) {
    case 'x':
        return Cat::x;
    case 'm':
        return Cat::m;
    case 'a':
        return Cat::a;
    default:
        assert(c == 's');
        return Cat::s;
    }
}

Cmp parse_cmp(const char c) {
    switch (c) {
    case '<':
        return Cmp::lt;
    default:
        assert(c == '>');
        return Cmp::gt;
    }
}

Cond parse_cond(const string &src) {
    const auto tokens =
        re_matches(R"(^([xmas])(<|>)([0-9]+):([a-z]+|[AR])$)", src);
    return Cond{
        Pred{parse_cat(tokens[0][0]), parse_cmp(tokens[1][0]), stoi(tokens[2])},
        tokens[3]};
}

Ruleset parse_ruleset(const string &src) {
    const auto tokens = split(",", src);
    assert(sz(tokens) > 1);
    vector<Cond> conds(sz(tokens) - 1);
    transform(cbegin(tokens), prev(cend(tokens)), begin(conds), parse_cond);
    return {conds, tokens.back()};
}

pair<Dest, Ruleset> parse_workflow(const string &src) {
    const auto it = src.find('{');
    assert(it != string::npos);

    const auto dest = src.substr(0, it);
    auto rules_src = src.substr(it + 1);
    rules_src.pop_back();

    return {dest, parse_ruleset(rules_src)};
}

Part parse_part(string src) {
    assert(src[0] == '{' && src.back() == '}');
    src.pop_back();
    src.erase(cbegin(src));

    const auto tokens = split(",", src);
    assert(sz(tokens) == 4);
    assert(tokens[0][0] == 'x');
    assert(tokens[1][0] == 'm');
    assert(tokens[2][0] == 'a');
    assert(tokens[3][0] == 's');

    Part result{};
    ranges::transform(tokens, begin(result),
                      [](const auto &x) { return stoi(x.substr(2)); });
    return result;
}

Dest new_dest(const Ruleset &ruleset, const Part &part) {
    for (const auto &c : ruleset.first) {
        const auto [p, dest] = c;
        const auto part_val = part[inof(p.cat)];
        if (p.cmp == Cmp::lt && part_val < p.val) return dest;
        if (p.cmp == Cmp::gt && part_val > p.val) return dest;
    }
    return ruleset.second;
}

bool process_and_return_acceptance(const Part &part,
                                   const map<Dest, Ruleset> &workflows) {
    Dest cur{"in"};
    while (cur != Accept && cur != Reject) {
        const auto &rules = workflows.at(cur);
        cur = new_dest(rules, part);
    }
    return cur == Accept;
}

vector<Pred> rule_predicate(const Ruleset &ruleset, const int irule) {
    assert(0 <= irule && irule <= sz(ruleset.first));
    if (irule == 0) return {ruleset.first[0].first};

    vector<Pred> result(irule);
    transform(cbegin(ruleset.first), cbegin(ruleset.first) + irule,
              begin(result),
              [](const auto &pd) { return negate_pred(pd.first); });
    if (irule < sz(ruleset.first)) result.push_back(ruleset.first[irule].first);
    return result;
}

Dest rule_dest(const Ruleset &ruleset, const int irule) {
    assert(0 <= irule && irule <= sz(ruleset.first));
    return irule == sz(ruleset.first) ? ruleset.second
                                      : ruleset.first[irule].second;
}

template <typename T> vector<T> unite(vector<T> a, const vector<T> &b) {
    a.insert(end(a), cbegin(b), cend(b));
    return a;
}

bool is_true(const Pred &p, const int val) {
    switch (p.cmp) {
    case Cmp::lt:
        return val < p.val;
    case Cmp::gt:
        return val > p.val;
    case Cmp::lte:
        return val <= p.val;
    default:
        assert(p.cmp == Cmp::gte);
        return val >= p.val;
    }
}

void conform_to_predicate(const Pred &p, set<int> &xs) {
    for (auto it = cbegin(xs); it != cend(xs);) {
        if (is_true(p, *it)) {
            ++it;
        } else {
            it = xs.erase(it);
        }
    }
}

set<int> complete_set() {
    vector<int> xs(4000);
    iota(begin(xs), end(xs), 1);
    return set<int>(cbegin(xs), cend(xs));
}

array<set<int>, 4> conform_to_predicates(const vector<Pred> &preds) {
    array<set<int>, 4> result;
    result.fill(complete_set());
    for (const auto &p : preds) conform_to_predicate(p, result[inof(p.cat)]);
    return result;
}

int main() {
    map<Dest, Ruleset> workflows;

    for (string line; getline(cin, line);) {
        if (empty(line)) break;
        const auto [dest, rules] = parse_workflow(line);
        workflows.emplace(dest, rules);
    }

    vector<Part> parts;

    for (string line; getline(cin, line);) {
        const auto part = parse_part(line);
        parts.push_back(part);
    }

    int result{};
    for (const auto &part : parts) {
        if (process_and_return_acceptance(part, workflows)) {
            result += accumulate(cbegin(part), cend(part), 0);
        }
    }
    cout << result << '\n';

    vector<vector<Pred>> acceptance_predicates;

    const auto recur = [&](const auto self, const vector<Pred> &cur,
                           const Dest &u) -> void {
        if (u == Accept) {
            acceptance_predicates.push_back(cur);
            return;
        }
        if (u == Reject) return;
        assert(workflows.count(u));

        for (int irule = 0; irule <= sz(workflows.at(u).first); ++irule) {
            self(self, unite(cur, rule_predicate(workflows.at(u), irule)),
                 rule_dest(workflows.at(u), irule));
        }
    };
    recur(recur, {}, "in");

    ll result2{};
    for (const auto &row : acceptance_predicates) {
        const auto satisfying = conform_to_predicates(row);
        result2 += accumulate(
            cbegin(satisfying), cend(satisfying), 1LL,
            [](const ll acc, const auto &xs) { return acc * llof(sz(xs)); });
    }
    cout << result2 << '\n';
    return 0;
}
