#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << x.first << ' ' << x.second;
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << '\n';
        os << *i;
    }
    return os;
}

constexpr bool same_parity(const int x, const int y) {
    return (x % 2) == (y % 2);
}

constexpr int reduction(const int x, const int y) {
    const int s = x + y;
    return s % 2 ? (s + 1) / 2 : s / 2;
}

pair<int, vector<pair<int, int>>> opt_reduction(const int n) {
    deque<int> xs;
    for (int i = n - 1; i >= 1; --i) xs.push_back(i);

    int ans = n;
    vector<pair<int, int>> peers;
    peers.reserve(n - 1);

    while (!xs.empty()) {
        auto it = cbegin(xs);
        while (it != cend(xs) && !same_parity(ans, *it)) ++it;

        if (it == cend(xs)) {
            it = cbegin(xs);
        }

        peers.emplace_back(*it, ans);
        ans = reduction(*it, ans);
        xs.erase(it);
    }

    return {ans, peers};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        const auto [ans, peers] = opt_reduction(n);
        cout << ans << '\n' << peers << '\n';
    }

    return 0;
}
