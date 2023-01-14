#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(int n, const vector<int> &xs) {
    if (any_of(cbegin(xs), cend(xs), [](const int x) { return x < 4; })) {
        return false;
    }

    const auto m = sz(xs);
    if (m > n) return false;

    n -= m;
    priority_queue<int> q;
    for (const auto x : xs) q.push(x - 4);

    while (n && !q.empty() && q.top() >= 4) {
        const auto x = q.top();
        q.pop();
        --n;
        if (x > 4) q.push(x - 4);
    }

    return !n;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<int> xs(m);
    for (auto &x : xs) cin >> x;

    cout << (is_possible(n, xs) ? "DA" : "NE") << '\n';
    return 0;
}
