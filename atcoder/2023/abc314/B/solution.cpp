#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<vector<int>> bets(N);

    for (int i = 0; i < N; ++i) {
        int c;
        cin >> c;

        vector<int> xs(c);
        for (auto &x : xs) cin >> x;
        bets[i] = xs;
    }

    int X;
    cin >> X;

    set<int> ans;
    int lo = INT_MAX;

    for (int i = 0; i < N; ++i) {
        const auto it = find(cbegin(bets[i]), cend(bets[i]), X);
        if (it == cend(bets[i])) continue;
        const auto c = sz(bets[i]);

        if (c == lo) {
            ans.insert(i + 1);
        } else if (c < lo) {
            lo = c;
            ans.clear();
            ans.insert(i + 1);
        }
    }

    cout << sz(ans) << '\n';
    for (auto i = ans.cbegin(); i != ans.cend(); ++i) {
        if (i != ans.cbegin()) cout << ' ';
        cout << *i;
    }
    cout << '\n';

    return 0;
}
