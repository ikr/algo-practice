#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    vector<int> xs(n);
    for (auto &x : xs) {
        cin >> x;
        --x;
    }

    vector<int> idx(n);
    for (int i = 0; i < n; ++i) idx[xs[i]] = i;

    set<int> w;
    for (int i = 0; i < k; ++i) {
        w.insert(idx[i]);
    }

    int result = *crbegin(w) - *cbegin(w);
    for (int d = 1; d + k <= n; ++d) {
        w.erase(idx[d - 1]);
        w.insert(idx[d + k - 1]);
        result = min(result, *crbegin(w) - *cbegin(w));
    }
    cout << result << '\n';
    return 0;
}
