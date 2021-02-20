#include <bits/stdc++.h>
using namespace std;

vector<int> digits_reversed(long long n) {
    vector<int> ans;

    while (n) {
        ans.push_back(n % 10);
        n /= 10;
    }

    return ans;
}

void remove_leading_zeros(vector<int> &ds) {
    for (auto it = ds.begin(); it != ds.end();) {
        if (*it != 0) break;
        it = ds.erase(it);
    }
}

long long number(const vector<int> &ds) {
    if (ds.empty()) return 0;

    long long ans = 0;
    long long mul = 1;
    for (auto it = ds.crbegin(); it != ds.crend(); ++it) {
        ans += (*it) * mul;
        mul *= 10LL;
    }
    return ans;
}

long long next_a(const long long x) {
    auto ds = digits_reversed(x);
    sort(rbegin(ds), rend(ds));
    const auto g1 = number(ds);

    sort(begin(ds), end(ds));
    remove_leading_zeros(ds);
    const auto g2 = number(ds);

    return g1 - g2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    long long a = n;
    for (int i = 1; i <= k; ++i) {
        a = next_a(a);
    }

    cout << a << '\n';
    return 0;
}
