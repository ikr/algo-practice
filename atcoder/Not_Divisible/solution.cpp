#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ll = long long;
using umi = unordered_map<int, int>;
template <typename T> constexpr int intof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int llof(const T x) {
    return static_cast<ll>(x);
}

vi uniques(const vi &xs) {
    umi counts;
    for (const int x : xs) {
        ++counts[x];
    }

    vi ans;
    copy_if(xs.cbegin(), xs.cend(), back_inserter(ans),
            [&counts](const int x) { return counts[x] == 1; });
    return ans;
}

int solve_on_uniques(vi xs) {
    sort(xs.begin(), xs.end());
    const int sz = xs.size();

    int ans = 0;
    ll prod = 1;
    for (int i = 0; i < sz; ++i) {
        const int x = xs[i];
        if (x == 1) return 1;
        if (gcd(prod, llof(x)) == 1) {
            ++ans;
        } else {
            bool found = false;

            for (int j = 0; j < i; ++j) {
                if (x % xs[j] == 0) {
                    found = true;
                    break;
                }
            }

            if (!found) ++ans;
        }
        prod *= x;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vi xs(sz, 0);
    for (auto &x : xs) cin >> x;
    cout << solve_on_uniques(uniques(xs)) << '\n';

    return 0;
}
