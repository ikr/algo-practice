#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Iter = string::const_iterator;

string join(const vector<string> &tokens) {
    string ans;
    for (const auto &t : tokens) ans += t;
    return ans;
}

pair<vector<string>, Iter> tokenize(const Iter last, const Iter it,
                                    vector<string> agg) {
    if (it == last || *it == ')') return {agg, it == last ? last : next(it)};

    if (*it == '(') {
        const auto [sub, subi] = tokenize(last, next(it), {});
        const string token = "(" + join(sub) + ")";
        agg.push_back(token);
        return tokenize(last, subi, agg);
    }

    assert(*it == '+' || *it == '*' || ('0' <= *it && *it <= '9'));
    agg.push_back(string(1, *it));
    return tokenize(last, next(it), agg);
}

void parenthesize_one(vector<string> &tokens,
                      const vector<string>::iterator it) {
    const string prefix = *prev(it);
    const string infix = *it;
    const string suffix = *next(it);

    const vector<string>::iterator jt = prev(it);
    tokens.erase(it, next(next(it)));
    *jt = "(" + prefix + infix + suffix + ")";
}

string parenthesize(const string &expr) {
    if (expr.size() == 3U) return expr;

    auto tokens = tokenize(cend(expr), cbegin(expr), {}).first;
    for (auto &t : tokens) {
        if (t[0] == '(') {
            const int sz = t.size();
            t = "(" + parenthesize(t.substr(1, sz - 2)) + ")";
        }
    }

    for (;;) {
        const auto it = find(begin(tokens), end(tokens), "+");
        if (it == end(tokens)) break;
        parenthesize_one(tokens, it);
    }

    return join(tokens);
}

template <typename Iter, typename R, typename Binop, typename Unaop>
R ttransform_reduce(Iter first, Iter last, R init, Binop binop, Unaop unaop) {
    R ans = init;

    for (auto it = first; it != last; ++it) {
        ans = binop(ans, unaop(*it));
    }

    return ans;
}

pair<ll, Iter> eval_expr(const Iter last, const Iter it, const ll reg);

pair<ll, Iter> eval_term(const Iter last, const Iter it) {
    if (*it == '(') return eval_expr(last, next(it), -1);
    assert('0' <= *it && *it <= '9');
    return {*it - '0', next(it)};
}

pair<ll, Iter> eval_expr(const Iter last, const Iter it, ll reg) {
    if (it == last || *it == ')') return {reg, it == last ? last : next(it)};

    if (reg == -1) {
        const auto [a, ai] = eval_term(last, it);
        return eval_expr(last, ai, a);
    } else {
        assert(*it == '*' || *it == '+');
        const auto [b, bi] = eval_term(last, next(it));
        return eval_expr(last, bi, *it == '*' ? reg * b : reg + b);
    }
}

ll eval_line(const string &line) {
    return eval_expr(cend(line), cbegin(line), -1).first;
}

ll solve(const vector<string> &lines) {
    return ttransform_reduce(cbegin(lines), cend(lines), 0LL, plus<ll>{},
                             eval_line);
}

int main() {
    vector<string> lines;

    for (string line; getline(cin, line);) {
        line.erase(remove(begin(line), end(line), ' '), cend(line));
        lines.push_back(parenthesize(line));
    }

    cout << solve(lines) << '\n';
    return 0;
}
