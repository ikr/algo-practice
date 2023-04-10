#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll kth_lowest(const vector<int> &A, const int K) {
    set<ll> xs{0};
    priority_queue<ll, vector<ll>, greater<ll>> q;
    q.push(0);

    while (sz(xs) <= (K + 1) * sz(A)) {
        const auto u = q.top();
        q.pop();

        for (const auto a : A) {
            if (xs.count(u + a)) continue;
            xs.insert(u + a);
            q.push(u + a);
        }
    }

    while (sz(xs) > K + 1) xs.erase(prev(cend(xs)));
    return *crbegin(xs);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &a : A) cin >> a;
    sort(begin(A), end(A));
    A.erase(unique(begin(A), end(A)), end(A));

    cout << kth_lowest(A, K) << '\n';
    return 0;
}
