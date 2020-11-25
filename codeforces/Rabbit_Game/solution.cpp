#include <bits/stdc++.h>
using namespace std;

int monotonic_head_size(const vector<int> &xs) {
    const int n = xs.size();
    int ans = 1;
    for (int i = 1; i < n; ++i) {
        if (xs[i] < xs[i - 1]) break;
        ++ans;
    }
    return ans;
}

int max_carrots(vector<int> &xs) {
    const int n = xs.size();
    const int a = monotonic_head_size(xs);
    reverse(begin(xs), end(xs));
    const int b = monotonic_head_size(xs);
    return min(n, a + b);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;

    cout << max_carrots(xs) << '\n';
    return 0;
}
