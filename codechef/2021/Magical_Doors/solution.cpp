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

int groups_count(const string &xs) {
    int ans = 1;
    char y = xs[0];

    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] != y) {
            ++ans;
            y = xs[i];
        }
    }

    return ans;
}

int min_usages(const string &xs) {
    const bool first_is_open = xs[0] == '1';
    const auto gs = groups_count(xs);
    return first_is_open ? (gs - 1) : gs;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        cout << min_usages(xs) << '\n';
    }

    return 0;
}
