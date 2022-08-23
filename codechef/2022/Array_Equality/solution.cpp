#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<int, int> frequences(const vector<int> &xs) {
    map<int, int> result;
    for (const auto x : xs) ++result[x];
    return result;
}

bool is_possible(const vector<int> &xs) {
    priority_queue<int> q;
    for (const auto [_, f] : frequences(xs)) q.push(f);

    while (sz(q) >= 2) {
        const auto a = q.top();
        q.pop();

        const auto b = q.top();
        q.pop();

        if (a - 1 > 0) q.push(a - 1);
        if (b - 1 > 0) q.push(b - 1);
    }

    return q.empty() || q.top() == 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        vector<int> xs(N);
        for (auto &x : xs) {
            cin >> x;
        }

        cout << (is_possible(xs) ? "Yes" : "No") << '\n';
    }

    return 0;
}
