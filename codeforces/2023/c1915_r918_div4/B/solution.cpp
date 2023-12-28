#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        vector<string> grid(3);
        map<char, int> fs;

        for (auto &row : grid) {
            cin >> row;
            assert(sz(row) == 3);

            for (const auto c : row) {
                if (c != '?') ++fs[c];
            }
        }

        vector<pair<char, int>> xs(cbegin(fs), cend(fs));
        const auto it = find_if(cbegin(xs), cend(xs),
                                [](const auto &p) { return p.second == 2; });
        cout << it->first << '\n';
    }

    return 0;
}
