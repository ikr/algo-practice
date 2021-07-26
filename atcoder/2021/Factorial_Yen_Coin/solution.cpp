#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi denominations() {
    vi ans{1};

    for (int i = 2; i <= 10; ++i) {
        ans.push_back(ans.back() * i);
    }

    reverse(begin(ans), end(ans));
    return ans;
}

int min_coins_num(const int p) {
    const auto ds = denominations();

    int x = p;
    int ans = 0;
    int i = 0;

    while (x) {
        while (ds[i] > x) ++i;

        ans += x / ds[i];
        x = x % ds[i];
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int p;
    cin >> p;

    cout << min_coins_num(p) << '\n';
    return 0;
}
