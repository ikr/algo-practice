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

    ll addition = 0;
    priority_queue<ll> pq;

    int t;
    cin >> t;
    while (t--) {
        int p;
        cin >> p;

        if (p == 1) {
            ll x;
            cin >> x;
            pq.push(-(x - addition));
        } else if (p == 2) {
            ll x;
            cin >> x;
            addition += x;
        } else {
            assert(p == 3);
            const ll x = -pq.top();
            pq.pop();
            cout << (x + addition) << '\n';
        }
    }

    return 0;
}
