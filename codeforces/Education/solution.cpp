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

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

vector<Promotion> promotions(const vi &wage, const vi &invest) {
    vector<Promotion> ans(sz(wage), {0, 0});

    for (int i = 1; i < sz(wage); ++i) {
        const ll gap = invest[i - 1] - ans[i - 1].balance;

        if (gap <= 0) {
            ans[i] = Promotion{ans[i - 1].days + 1, -gap};
            continue;
        }

        const ll work_days = div_ceil(gap, llof(wage[i - 1]));

        ans[i] = Promotion{ans[i - 1].days + work_days + 1,
                           ans[i - 1].balance + work_days * wage[i - 1] -
                               invest[i - 1]};
    }

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
