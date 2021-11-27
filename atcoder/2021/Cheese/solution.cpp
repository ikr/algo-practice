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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    ll w;
    cin >> n >> w;

    ll ans{};
    priority_queue<pii> q;

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;

        q.emplace(a, b);
    }

    while (!q.empty() && w > 0) {
        const auto [a, b] = q.top();
        q.pop();

        const ll gramms = min(w, llof(b));
        ans += a * gramms;
        w -= gramms;
    }

    cout << ans << '\n';
    return 0;
}
