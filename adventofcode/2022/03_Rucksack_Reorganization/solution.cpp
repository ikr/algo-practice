#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int score(const char x) {
    if (islower(x, locale::classic())) {
        return inof(x) - inof('a') + 1;
    }
    return inof(x) - inof('A') + 27;
}

char intersection(string xs, string ys) {
    sort(begin(xs), end(xs));
    sort(begin(ys), end(ys));
    string zs;

    set_intersection(cbegin(xs), cend(xs), cbegin(ys), cend(ys),
                     back_inserter(zs));
    return zs[0];
}

int sum_of_prios_of_odd_items(const vector<pair<string, string>> &src) {
    return transform_reduce(cbegin(src), cend(src), 0, plus<int>{},
                            [](const auto ab) -> int {
                                return score(intersection(ab.first, ab.second));
                            });
}

int main() {
    vector<pair<string, string>> src;

    for (string line; getline(cin, line);) {
        src.emplace_back(line.substr(0, sz(line) / 2),
                         line.substr(sz(line) / 2));
    }

    cout << sum_of_prios_of_odd_items(src) << '\n';
    return 0;
}
