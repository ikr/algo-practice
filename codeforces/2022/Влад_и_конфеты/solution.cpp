#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(vector<int> xs) {
    priority_queue<int> q(cbegin(xs), cend(xs));

    while (sz(q) > 2) {
        const auto a = q.top();
        q.pop();

        const auto b = q.top();
        q.pop();

        if (a - b > 1) return false;
        q.push(q.top());
    }

    if (sz(q) == 2) {
        const auto a = q.top();
        q.pop();

        const auto b = q.top();
        q.pop();

        return abs(a - b) < 2;
    }

    return q.empty() || q.top() == 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << (is_possible(move(xs)) ? "YES" : "NO") << '\n';
    }

    return 0;
}
