#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int my_total_score(const vector<pii> &plays) {
    return transform_reduce(cbegin(plays), cend(plays), 0, plus<int>{},
                            [](const auto p1p2) {
                                const auto [p1, p2] = p1p2;
                                if (p1 == p2) {
                                    return 3 + p2 + 1;
                                }

                                if (p1 == 0 && p2 == 2) {
                                    return 0 + p2 + 1;
                                }

                                if (p2 == 0 && p1 == 2) {
                                    return 6 + p2 + 1;
                                }

                                if (p1 + 1 == p2) {
                                    return 6 + p2 + 1;
                                }

                                return 0 + p2 + 1;
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
