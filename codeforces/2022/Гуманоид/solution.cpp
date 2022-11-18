#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

queue<int> queue_of(const vector<int> &xs) {
    queue<int> result;
    for (const auto x : xs) result.push(x);
    return result;
}

vector<queue<int>> strategies() {
    return {queue_of({2, 2, 3}), queue_of({2, 3, 2}), queue_of({3, 2, 2})};
}

int max_yield_using(const vector<int> &src, ll h, queue<int> mul) {
    int result{};
    multiset<ll> xs(cbegin(src), cend(src));

    while (!xs.empty()) {
        const auto lo = *cbegin(xs);
        if (lo >= h) {
            if (mul.empty()) break;
            h *= mul.front();
            mul.pop();
            continue;
        }

        const auto it = xs.lower_bound(h);
        assert(it != cbegin(xs));

        const auto x = *prev(it);
        h += x / 2;
        xs.erase(prev(it));
        ++result;
    }

    return result;
}

int max_yield(const vector<int> &src, const ll h) {
    int result{};
    for (const auto &mul : strategies()) {
        result = max(result, max_yield_using(src, h, mul));
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, h;
        cin >> n >> h;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_yield(xs, h) << '\n';
    }

    return 0;
}
