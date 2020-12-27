#include <bits/stdc++.h>
using namespace std;
using Words = vector<string>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

template <typename Iter, typename R, typename Binop, typename Unaop>
R ttransform_reduce(Iter first, Iter last, R init, Binop binop, Unaop unaop) {
    return inner_product(first, last, first, init, binop,
                         [&unaop](const auto &x,
                                  __attribute__((unused))
                                  const auto &x_) { return unaop(x); });
}

vector<string> split(const regex &delim, const string &s) {
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), delim, -1),
                          sregex_token_iterator{});
}

string drop_last(string s) {
    s.erase(prev(cend(s)), cend(s));
    return s;
}

int solve(const vector<pair<Words, Words>> &input) {
    const auto insert_into_set = [](set<string> agg, const Words &ws) {
        agg.insert(cbegin(ws), cend(ws));
        return agg;
    };

    const auto all_ingridients = ttransform_reduce(
        cbegin(input), cend(input), set<string>{}, insert_into_set,
        [](const auto &food) { return food.first; });

    const auto all_allergens = ttransform_reduce(
        cbegin(input), cend(input), set<string>{}, insert_into_set,
        [](const auto &food) { return food.second; });

    cout << all_ingridients << '\n' << all_allergens << '\n';

    return 0;
}

int main() {
    vector<pair<Words, Words>> input;

    for (string line; getline(cin, line);) {
        const auto parts = split(regex(" \\(contains "), line);
        const auto ingridients = split(regex(" "), parts[0]);
        const auto allergens = split(regex(", "), drop_last(parts[1]));
        input.emplace_back(ingridients, allergens);
    }

    cout << solve(input) << '\n';
    return 0;
}
