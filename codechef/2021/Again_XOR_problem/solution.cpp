#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int num_ones_in_t(const string &xs, const int k) {
    if (k == sz(xs)) {
        return inof(count(cbegin(xs), cend(xs), '1'));
    }

    if (k == 1) {
        int ans{};

        for (const auto x : xs) {
            ans ^= (inof(x) - inof('0'));
        }

        return ans;
    }

    int ans{};

    for (int i = k; i < sz(xs); ++i) {
        if (xs[i] != xs[i - k]) ++ans;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        string xs(n, ' ');
        cin >> xs;
        cout << num_ones_in_t(xs, k) << '\n';
    }

    return 0;
}
