#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_final_size(const vi &xs) {
    map<int, int> fs;
    for (const int x : xs) ++fs[x];

    priority_queue<int> q;
    for (const auto [_, v] : fs) q.push(v);

    while (!q.empty()) {
        if (sz(q) == 1) return q.top();

        const int a = q.top();
        q.pop();

        const int b = q.top();
        q.pop();

        if (a - 1) q.push(a - 1);
        if (b - 1) q.push(b - 1);
    }

    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> xs(n);
        for (auto &x : xs) cin >> x;
        cout << min_final_size(xs) << '\n';
    }

    return 0;
}
