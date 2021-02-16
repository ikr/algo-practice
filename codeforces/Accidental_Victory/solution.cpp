#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

map<int, int> gather_counts(const vector<int> &xs) {
    map<int, int> ans;
    for (const int x : xs) ++ans[x];
    return ans;
}

vector<int> possible_winner_positions(const vector<int> &xs) {
    const int hi = *max_element(cbegin(xs), cend(xs));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;
        cout << possible_winner_positions() << '\n';
    }

    return 0;
}
