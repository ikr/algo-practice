#include <bits/stdc++.h>
using namespace std;
using Iter = list<int>::const_iterator;

template <typename T> ostream &operator<<(ostream &os, const list<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

pair<int, list<int>> solve(vector<int> &xs) {
    const int n = xs.size();
    if (n <= 2) return {0, list<int>(cbegin(xs), cend(xs))};

    sort(rbegin(xs), rend(xs));
    list<int> ans{xs[0], xs[1]};
    queue<pair<Iter, Iter>> q;
    q.emplace(cbegin(ans), next(cbegin(ans)));

    for (int i = 2; i < n; ++i) {
        const auto [lo, hi] = q.front();
        q.pop();
        const auto mid = ans.insert(hi, xs[i]);
        q.emplace(lo, mid);
        q.emplace(mid, hi);
    }

    const int count = n % 2 == 0 ? (n / 2 - 1) : n / 2;
    return {count, ans};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;
    const auto [cnt, ys] = solve(xs);

    cout << cnt << '\n';
    cout << ys << '\n';

    return 0;
}
