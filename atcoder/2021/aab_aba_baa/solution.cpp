#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vvll combinations(const int n, const int k) {
    assert(k <= n);
    vvll ans(n + 1, vll(k + 1, 1));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= min(i, k); ++j) {
            ans[i][j] = i == j ? 1 : ans[i - 1][j - 1] + ans[i - 1][j];
        }
    }

    return ans;
}

string kth_element(int a, int b, ll k) {
    const auto cs = combinations(a + b + 1, a + b + 1);
    const auto i_choose_j = [&cs](const int i, const int j) -> ll {
        assert(j <= i);
        return cs[i][j];
    };

    string ans;

    while (a || b) {
        if (!a) {
            ans += string(b, 'b');
            break;
        }

        if (!b) {
            ans += string(a, 'a');
            break;
        }

        assert(a && b);

        const auto starting_with_a = i_choose_j(a + b - 1, b);

        if (starting_with_a < k) {
            ans += 'b';
            --b;
            k -= starting_with_a;
        } else {
            ans += 'a';
            --a;
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int a, b;
    cin >> a >> b;

    ll k;
    cin >> k;

    cout << kth_element(a, b, k) << '\n';
    return 0;
}
