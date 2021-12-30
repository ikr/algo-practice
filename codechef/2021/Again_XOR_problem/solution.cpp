#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int xor_every(const string &xs) {
    int ans{};

    for (const auto x : xs) {
        ans ^= (inof(x) - inof('0'));
    }

    return ans;
}

vi to_ints(const string &xs) {
    vi ans(sz(xs), 0);
    transform(cbegin(xs), cend(xs), begin(ans),
              [](const char d) { return inof(d) - inof('0'); });
    return ans;
}

int num_ones_in_t(const string &xs, const int k) {
    if (k == sz(xs)) {
        return inof(count(cbegin(xs), cend(xs), '1'));
    }

    if (k == 1) {
        return xor_every(xs);
    }

    const auto ys = to_ints(xs);
    vi ss(sz(ys));
    partial_sum(cbegin(ys), cend(ys), begin(ss));

    int ans{};
    for (int i0 = 0; i0 + sz(ys) - k < sz(ys); ++i0) {
        const auto m = sz(ys) - k;
        const auto l = i0;
        const auto r = i0 + m;
        const auto s = ss[r] - (l == 0 ? 0 : ss[l - 1]);

        ans += (s % 2);
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
