#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_total_cost(const vector<int> &A, const vector<int> &W) {
    const auto n = sz(A);
    vector<priority_queue<int, vector<int>, greater<int>>> pqs(n);

    for (int i = 0; i < n; ++i) {
        pqs[A[i]].push(W[i]);
    }

    int result{};
    for (auto &pq : pqs) {
        while (sz(pq) > 1) {
            result += pq.top();
            pq.pop();
        }
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> A(n);
    for (auto &a : A) {
        cin >> a;
        --a;
    }

    vector<int> W(n);
    for (auto &w : W) cin >> w;

    cout << min_total_cost(A, W) << '\n';
    return 0;
}
