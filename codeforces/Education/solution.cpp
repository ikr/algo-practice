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

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

struct Promotion final {
    ll days;
    ll balance;
};

vector<Promotion> promotions(const vi &wage, const vi &invest) {
    vector<Promotion> ans(sz(wage));
    return ans;
}

ll min_days(const int goal, const vi &wage, const vi &invest) {
    const auto ps = promotions(wage, invest);
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, c;
        cin >> n >> c;

        vi a(n);
        for (auto &x : a) cin >> x;

        vi b(n - 1);
        for (auto &x : b) cin >> x;

        cout << min_days(c, a, b) << '\n';
    }

    return 0;
}
