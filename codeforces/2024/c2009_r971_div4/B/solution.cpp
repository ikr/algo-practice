#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<string> grid(n);
        for (auto &row : grid) cin >> row;

        reverse(begin(grid), end(grid));
        vector<int> ans;
        ans.reserve(n);

        for (const auto &row : grid) {
            const auto i = find(cbegin(row), cend(row), '#') - cbegin(row);
            ans.push_back(i + 1);
        }
        cout << ans << '\n';
    }

    return 0;
}
