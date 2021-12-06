#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

using Population = array<ll, 9>;

Population initial_population(const vll &xs) {
    Population result{};
    for (const auto x : xs) {
        ++result[x];
    }
    return result;
}

Population evolve(const Population &p) {
    const auto z = p[0];

    Population result{};
    for (int i = 8; i >= 1; --i) {
        result[i - 1] = p[i];
    }
    result[6] += z;
    result[8] = z;
    return result;
}

ll population_after_256_days(const vll &xs) {
    auto p = initial_population(xs);

    for (int i = 0; i < 256; ++i) {
        p = evolve(p);
    }

    return accumulate(cbegin(p), cend(p), 0LL);
}

int main() {
    string src;
    cin >> src;

    const auto nums_src = split(",", src);
    vll xs(sz(nums_src));
    transform(cbegin(nums_src), cend(nums_src), begin(xs),
              [](const auto &x) { return stoll(x); });

    cout << population_after_256_days(xs) << '\n';
    return 0;
}
