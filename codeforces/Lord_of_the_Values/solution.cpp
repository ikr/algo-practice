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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;
        assert(sz(xs) % 2 == 0);

        const int ops = (sz(xs) / 2) * 6;
        cout << ops << '\n';

        for (int i = 0; i < sz(xs); i += 2) {
            const int j = i + 1;

            for (const auto op : vi{1, 2, 1, 1, 2, 1}) {
                cout << op << ' ' << (i + 1) << ' ' << (j + 1) << '\n';
            }
        }
    }

    return 0;
}
