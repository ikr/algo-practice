#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> digits_reversed(ll x) {
    vector<int> ans;
    while (x) {
        ans.push_back(x % 10);
        x /= 10;
    }
    return ans;
}

tuple<int, int, int> gather_mod012_counts(const vector<int> &xs) {
    int c0 = 0;
    int c1 = 0;
    int c2 = 0;

    for (const int x : xs) {
        switch (x % 3) {
        case 1:
            ++c1;
            break;
        case 2:
            ++c2;
            break;
        default:
            assert(x % 3 == 0);
            ++c0;
        }
    }

    return {c0, c1, c2};
}

int recur(const int c1, const int c2) {
    if ((c1 + 2 * c2) % 3 == 0) return c1 + c2;

    const int o1 = c1 > 0 ? recur(c1 - 1, c2) : 0;
    const int o2 = c2 > 0 ? recur(c1, c2 - 1) : 0;
    return max(o1, o2);
}

int min_removals(const ll x) {
    const auto ds = digits_reversed(x);
    const int n = ds.size();
    const auto [c0, c1, c2] = gather_mod012_counts(ds);

    const int len = c0 + recur(c1, c2);
    return len ? n - len : -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll x;
    cin >> x;
    cout << min_removals(x) << '\n';
    return 0;
}
