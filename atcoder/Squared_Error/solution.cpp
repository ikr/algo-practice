#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

ll sum_up(const vector<int> &xs) {
    vector<int> fs(401, 0);

    for (const int x : xs) {
        assert(x + 200 >= 0);
        assert(x + 200 <= 400);
        ++fs[x + 200];
    }

    ll ans = 0;

    for (int i = 0; i < 400; ++i) {
        for (int j = i + 1; j <= 400; ++j) {
            const int a = i - 200;
            const int b = j - 200;

            ans += llof(fs[i]) * llof(fs[j]) * (a - b) * (a - b);
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    cout << sum_up(xs) << '\n';
    return 0;
}
