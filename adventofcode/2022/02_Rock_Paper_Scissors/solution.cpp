#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

int my_total_score(const vector<pii> &plays) {
    return transform_reduce(cbegin(plays), cend(plays), 0, plus<int>{},
                            [](const auto p) {
                                const auto [opp, out] = p;

                                if (out == 1) {
                                    return 3 + opp + 1;
                                }

                                if (out == 0) {
                                    return 0 + ((opp - 1 + 3) % 3) + 1;
                                }

                                return 6 + ((opp + 1) % 3) + 1;
                            });
}

int main() {
    vector<pii> plays;

    for (string line; getline(cin, line);) {
        const auto p1 = inof(line[0]) - inof('A');
        const auto p2 = inof(line[2]) - inof('X');
        plays.emplace_back(p1, p2);
    }

    cout << my_total_score(plays) << '\n';
    return 0;
}
