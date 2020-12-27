#include <bits/stdc++.h>
using namespace std;
using Words = vector<string>;

template <typename K, typename V>
ostream &operator<<(ostream &os, const multimap<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
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

template <typename T> struct take_first final {
    constexpr T operator()(const pair<T, T> &p) const { return p.first; }
};

template <typename T> struct take_second final {
    constexpr T operator()(const pair<T, T> &p) const { return p.second; }
};

multimap<string, string>
ingridients_x_allergens(const vector<pair<Words, Words>> &foods) {
    const auto insert_into_set = [](set<string> agg, const Words &ws) {
        agg.insert(cbegin(ws), cend(ws));
        return agg;
    };

    const auto all_ingridients =
        ttransform_reduce(cbegin(foods), cend(foods), set<string>{},
                          insert_into_set, take_first<Words>{});

    const auto all_allergens =
        ttransform_reduce(cbegin(foods), cend(foods), set<string>{},
                          insert_into_set, take_second<Words>{});

    const auto pair_with = [](const string &a, const set<string> &bs) {
        vector<pair<string, string>> ans(bs.size());
        transform(cbegin(bs), cend(bs), begin(ans), [&a](const string &b) {
            return pair{a, b};
        });
        return ans;
    };

    auto mm = ttransform_reduce(
        cbegin(all_ingridients), cend(all_ingridients),
        multimap<string, string>{},
        [](auto agg, const auto &ps) {
            agg.insert(cbegin(ps), cend(ps));
            return agg;
        },
        [&](const string &w) { return pair_with(w, all_allergens); });

    return mm;
}

bool contains(const Words &haystack, const string &needle) {
    return find(cbegin(haystack), cend(haystack), needle) != cend(haystack);
}

int solve(const vector<pair<Words, Words>> &foods) {
    auto mm = ingridients_x_allergens(foods);

    const auto all_ingridients = ttransform_reduce(
        cbegin(mm), cend(mm), set<string>{},
        [](auto agg, const string &w) {
            agg.insert(w);
            return agg;
        },
        take_first<string>{});

    for (const auto &[ings, algs] : foods) {
        for (const auto &ing : ings) {
            const auto [first, last] = mm.equal_range(ing);
            for (auto it = first; it != last;) {
                if (contains(algs, it->second)) {
                    ++it;
                } else {
                    it = mm.erase(it);
                }
            }
        }
    }

    cout << all_ingridients << '\n' << mm << '\n';

    return count_if(cbegin(all_ingridients), cend(all_ingridients),
                    [&](const auto &ing) { return mm.count(ing) == 0; });
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
