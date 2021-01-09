#include <bits/stdc++.h>
using namespace std;
static constexpr int LIM = 2 * 1e9;

int chain_size(const int x) {
    if (x <= 1) return x;

    if (x % 2) {
        return 1 + chain_size(3 * x + 1);
    }

    return 1 + chain_size(x / 2);
}

int max_chain_size_in_range(const int lo, const int hi) {
    assert(lo <= hi);

    int ans = 0;
    for (int x = lo; x <= hi; ++x) {
        ans = max(ans, chain_size(x));
    }
    return ans;
}

int main() {
    for (string line; getline(cin, line);) {
        stringstream ss(line);
        int a, b;
        ss >> a >> b;

        cout << a << ' ' << b << ' '
             << max_chain_size_in_range(min(a, b), max(a, b)) << '\n';
    }

    return 0;
}
