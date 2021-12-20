#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int num_of_likable(const vi &xs, const int n) {
    const auto it = lower_bound(cbegin(xs), cend(xs), n);
    return inof(distance(cbegin(xs), it)) + (*it == n ? 1 : 0);
}

static constexpr ll N_MAX = 1'000'000'000LL;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    set<int> xss;

    for (int i = 1; llof(i) * i <= N_MAX; ++i) {
        xss.insert(i * i);
    }

    for (int i = 1; llof(i) * i * i <= N_MAX; ++i) {
        xss.insert(i * i * i);
    }

    vi xs(cbegin(xss), cend(xss));

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        cout << num_of_likable(xs, n) << '\n';
    }

    return 0;
}
