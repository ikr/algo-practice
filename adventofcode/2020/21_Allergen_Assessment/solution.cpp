#include <bits/stdc++.h>
using namespace std;
using Words = vector<string>;

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

string join(const map<string, string> &xs) {
    return accumulate(cbegin(xs), cend(xs), string{},
                      [](auto agg, const auto &p) {
                          if (!agg.empty()) agg += ',';
                          agg += p.second;
                          return agg;
                      });
}

pair<string, string> find_singleton(const multimap<string, string> &mm) {
    for (const auto &[alg, ing] : mm) {
        if (mm.count(alg) == 1) return {alg, ing};
    }
    assert(false && "find_singleton");
    return {};
}

string solve(const vector<pair<Words, Words>> &foods) {
    auto mm = derive_allergens(foods);
    map<string, string> ans;

    while (!mm.empty()) {
        const auto [alg, ing] = find_singleton(mm);
        ans.emplace(alg, ing);

        for (auto it = cbegin(mm); it != cend(mm);) {
            if (it->second == ing) {
                it = mm.erase(it);
            } else {
                ++it;
            }
        }
    }

    return join(ans);
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
