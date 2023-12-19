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

struct Cond final {
    Cat cat;
    Cmp cmp;
    int val;
    Dest dest;
};

using Rule = variant<Cond, Dest>;

template <class... Ts> struct dispatch : Ts... {
    using Ts::operator()...;
};

static const Dest ImmediateAccept{"A"};
static const Dest ImmediateReject{"R"};

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

ostream &operator<<(ostream &os, const Cond &c) {
    os << '(' << c.cat << ' ' << c.cmp << ' ' << c.val << " ⇒ " << c.dest
       << ')';
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
    return Cond{parse_cat(tokens[0][0]), parse_cmp(tokens[1][0]),
                stoi(tokens[2]), tokens[3]};
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
    cerr << "tokens: " << tokens << endl;
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

int main() { return 0; }
