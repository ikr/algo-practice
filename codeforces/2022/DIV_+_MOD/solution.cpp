#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int fn_f(const int a, const int x) { return x / a + x % a; }

int f_max(const int l, const int r, const int a) {
    const auto ph = r % a;
    const auto pre_z = r - ph - 1;
    if (l <= pre_z) return max({fn_f(a, l), fn_f(a, pre_z), fn_f(a, r)});
    return max(fn_f(a, l), fn_f(a, r));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int l, r, a;
        cin >> l >> r >> a;
        cout << f_max(l, r, a) << '\n';
    }

    return 0;
}
