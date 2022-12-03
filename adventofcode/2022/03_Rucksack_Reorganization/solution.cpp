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

string intersection(string xs, string ys) {
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));

    sort(begin(ys), end(ys));
    ys.erase(unique(begin(ys), end(ys)), end(ys));

    string zs;

    set_intersection(cbegin(xs), cend(xs), cbegin(ys), cend(ys),
                     back_inserter(zs));
    return zs;
}

char intersection(const array<string, 3> &xss) {
    return intersection(intersection(xss[0], xss[1]), xss[2])[0];
}

int sum_of_prios_of_group_badges(const vector<array<string, 3>> &groups) {
    return transform_reduce(
        cbegin(groups), cend(groups), 0, plus<int>{},
        [](const auto &g) -> int { return score(intersection(g)); });
}

int main() {
    vector<string> lines;

    for (string line; getline(cin, line);) {
        lines.emplace_back(line);
    }

    vector<array<string, 3>> groups(sz(lines) / 3);
    for (int i = 0; i < sz(groups); ++i) {
        for (int j = 0; j < 3; ++j) {
            groups[i][j] = lines[i * 3 + j];
        }
    }

    cout << sum_of_prios_of_group_badges(groups) << '\n';
    return 0;
}
