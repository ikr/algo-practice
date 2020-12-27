#include <bits/stdc++.h>
#include <numeric>
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

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
    return os;
}

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

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
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

multimap<string, string>
allergens_x_ingridients(const vector<pair<Words, Words>> &foods) {
    multimap<string, string> ans;

    for (const auto &[ings, algs] : foods) {
        for (const auto &alg : algs) {
            if (ans.count(alg)) continue;
            for (const auto &ing : ings) ans.emplace(alg, ing);
        }
    }

    return ans;
}

bool contains(const Words &haystack, const string &needle) {
    return find(cbegin(haystack), cend(haystack), needle) != cend(haystack);
}

multimap<string, string>
derive_allergens(const vector<pair<Words, Words>> &foods) {
    auto mm = allergens_x_ingridients(foods);

    for (auto it = cbegin(mm); it != cend(mm);) {
        const auto [y, x] = *it;

        bool confirmed = true;
        for (const auto &[ings, algs] : foods) {

            if (contains(algs, y) && !contains(ings, x)) {
                confirmed = false;
                break;
            }
        }

        if (confirmed) {
            ++it;
        } else {
            it = mm.erase(it);
        }
    }

    return mm;
}

int solve(const vector<pair<Words, Words>> &foods) {
    const auto mm = derive_allergens(foods);

    const auto ingridients_with_allergens = accumulate(
        cbegin(mm), cend(mm), set<string>{}, [](auto agg, const auto &p) {
            agg.insert(p.second);
            return agg;
        });

    int ans = 0;

    for (const auto &[ings, algs] : foods) {
        for (const auto &ing : ings) {
            if (!ingridients_with_allergens.count(ing)) ++ans;
        }
    }

    return ans;
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
