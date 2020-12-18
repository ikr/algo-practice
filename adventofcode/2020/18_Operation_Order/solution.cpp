#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Iter = string::const_iterator;

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
        lines.push_back(line);
    }

    cout << solve(lines) << '\n';
    return 0;
}
