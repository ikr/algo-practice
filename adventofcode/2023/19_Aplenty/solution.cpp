#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const array<T, 4> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
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
enum class Cmp { lt, gt };
using Dest = string;

struct Pred final {
    Cat cat;
    Cmp cmp;
    int val;
};

using Cond = pair<Pred, Dest>;

using Rule = variant<Cond, Dest>;
using Part = array<int, 4>;

template <class... Ts> struct dispatch : Ts... {
    using Ts::operator()...;
};

static const Dest Accept{"A"};
static const Dest Reject{"R"};

ostream &operator<<(ostream &os, const Cat &c) {
    switch (c) {
    case Cat::x:
        os << 'x';
        break;
    case Cat::m:
        os << 'm';
        break;
    case Cat::a:
        os << 'a';
        break;
    case Cat::s:
        os << 's';
        break;
    }
    return os;
}

ostream &operator<<(ostream &os, const Cmp &c) {
    switch (c) {
    case Cmp::lt:
        os << '<';
        break;
    case Cmp::gt:
        os << '>';
        break;
    }
    return os;
}

ostream &operator<<(ostream &os, const Pred &p) {
    os << '|' << p.cat << ' ' << p.cmp << ' ' << p.val << '|';
    return os;
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

Rule parse_rule(const string &src) {
    if (src.find(':') == string::npos) return src;
    return parse_cond(src);
}

ostream &operator<<(ostream &os, const Rule &r) {
    visit(dispatch{[&](const Cond &c) { os << c; },
                   [&](const Dest &d) { os << "Dest:" << d; }},
          r);
    return os;
}

vector<Rule> parse_rules(const string &src) {
    const auto tokens = split(",", src);
    vector<Rule> result(sz(tokens));
    ranges::transform(tokens, begin(result), parse_rule);
    return result;
}

pair<Dest, vector<Rule>> parse_workflow(const string &src) {
    const auto it = src.find('{');
    assert(it != string::npos);

    const auto dest = src.substr(0, it);
    auto rules_src = src.substr(it + 1);
    rules_src.pop_back();

    return {dest, parse_rules(rules_src)};
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

Dest new_dest(const vector<Rule> &rules, const Part &part) {
    for (const auto &r : rules) {
        const auto outcome =
            visit(dispatch{[&](const Cond &c) -> optional<Dest> {
                               const auto [p, dest] = c;
                               const auto part_val = part[inof(p.cat)];
                               if (p.cmp == Cmp::lt && part_val < p.val) {
                                   return dest;
                               }
                               if (p.cmp == Cmp::gt && part_val > p.val) {
                                   return dest;
                               }
                               return nullopt;
                           },
                           [&](const Dest &d) -> optional<Dest> { return d; }},
                  r);
        if (outcome) return *outcome;
    }
    assert(false && "new_dest");
    return "";
}

bool process_and_return_acceptance(const Part &part,
                                   const map<Dest, vector<Rule>> &workflows) {
    Dest cur{"in"};
    while (cur != Accept && cur != Reject) {
        const auto &rules = workflows.at(cur);
        cur = new_dest(rules, part);
    }
    return cur == Accept;
}

int main() {
    map<Dest, vector<Rule>> workflows;

    for (string line; getline(cin, line);) {
        if (empty(line)) break;
        const auto [dest, rules] = parse_workflow(line);
        cerr << "dest:" << dest << " rules:" << rules << endl;
        workflows.emplace(dest, rules);
    }

    vector<Part> parts;

    for (string line; getline(cin, line);) {
        const auto part = parse_part(line);
        cerr << "part:" << part << endl;
        parts.push_back(part);
    }

    int result{};
    for (const auto &part : parts) {
        if (process_and_return_acceptance(part, workflows)) {
            result += accumulate(cbegin(part), cend(part), 0);
        }
    }
    cout << result << '\n';
    return 0;
}
