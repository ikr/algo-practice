#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

vector<int> gather_prevs(const vector<int> &xs, const int k) {
    const int n = xs.size();
    stack<int> s;
    vector<int> ans(n, -1);

    for (int i = 0; i < n; ++i) {
        while (!s.empty() && abs(xs[s.top()] - xs[i]) > k) {
            s.pop();
        }

        if (!s.empty()) ans[i] = s.top();
        s.push(i);
    }

    return ans;
}

int solve(const vector<int> &xs, const int k) {
    const int n = xs.size();
    const auto prevs = gather_prevs(xs, k);

    vector<int> dp(n, 1);
    for (int i = 1; i < n; ++i) {
        if (prevs[i] != -1) {
            dp[i] = dp[prevs[i]] + 1;
        }
    }

    cout << prevs << '\n';
    cout << dp << '\n';

    return *max_element(cbegin(dp), cend(dp));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, K;
    cin >> N >> K;

    vector<int> xs(N, 0);
    for (auto &x : xs) cin >> x;

    cout << solve(xs, K) << '\n';

    return 0;
}
