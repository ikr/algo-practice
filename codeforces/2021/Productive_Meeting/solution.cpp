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

vector<pii> talks(const vi &xs) {
    priority_queue<pii> q;
    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i]) q.emplace(xs[i], i + 1);
    }

    vector<pii> ans;

    while (sz(q) > 1) {
        auto [n1, id1] = q.top();
        q.pop();

        auto [n2, id2] = q.top();
        q.pop();

        ans.emplace_back(id1, id2);

        if (n1 - 1) {
            q.emplace(n1 - 1, id1);
        }

        if (n2 - 1) {
            q.emplace(n2 - 1, id2);
        }
    }

    return ans;
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

        vi xs(n);
        for (auto &x : xs) cin >> x;

        const auto ans = talks(xs);
        cout << sz(ans) << '\n';
        for (const auto [a, b] : ans) {
            cout << a << ' ' << b << '\n';
        }
    }

    return 0;
}
