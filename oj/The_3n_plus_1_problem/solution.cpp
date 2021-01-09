#include <bits/stdc++.h>
using namespace std;
static constexpr int LIM = 2 * 1e9;

int chain_size(vector<int> &memo, const int x) {
    if (memo[x] == -1) {
        if (x <= 1) {
            memo[x] = x;
        } else if (x % 2) {
            memo[x] = 1 + chain_size(memo, 3 * x + 1);
        } else {
            memo[x] = 1 + chain_size(memo, x / 2);
        }
    }
    return memo[x];
}

int max_chain_size_in_range(vector<int> &memo, const int lo, const int hi) {
    assert(lo <= hi);

    int ans = 0;
    for (int x = lo; x <= hi; ++x) {
        ans = max(ans, chain_size(memo, x));
    }
    return ans;
}

int main() {
    vector<int> memo(LIM, -1);

    for (string line; getline(cin, line);) {
        stringstream ss(line);
        int a, b;
        ss >> a >> b;

        cout << a << ' ' << b << ' '
             << max_chain_size_in_range(memo, min(a, b), max(a, b)) << '\n';
    }

    return 0;
}
