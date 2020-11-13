#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

bool straight(const int n, const int a, const int b) {
    assert(a <= b);
    return b - a <= a + n - b;
}

int lowest_upshift_index(const int n, const vector<ll> &xs, const int i) {
    assert(i >= 0);
    const int w = xs.size();
    assert(i < w);

    if (i == 0 || !straight(n, xs[i - 1], xs[i])) return i;
    if (straight(n, xs[0], xs[i])) return 0;

    int lo = 0;
    int hi = i - 1;

    while (hi - lo != 1) {
        const int mid = lo + (hi - lo) / 2;
        if (straight(n, xs[mid], xs[i])) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    return hi;
}

int highest_downshift_index(const int n, const vector<ll> &xs, const int i) {
    assert(i >= 0);
    const int w = xs.size();
    assert(i < w);

    if (i == w - 1 || !straight(n, xs[i], xs[i + 1])) return i;
    if (straight(n, xs[i], xs[w - 1])) return w - 1;

    int lo = i + 1;
    int hi = w - 1;

    while (hi - lo != 1) {
        const int mid = lo + (hi - lo) / 2;
        if (straight(n, xs[i], xs[mid])) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return lo;
}

vector<ll> gather_partial_sums(const vector<ll> &xs) {
    vector<ll> ans(xs.size() + 1, 0);
    partial_sum(cbegin(xs), cend(xs), next(begin(ans)));
    return ans;
}

ll moves_to(const int n, const vector<ll> &xs, const vector<ll> &ss,
            const int i) {
    ll ans = 0;
    // cout << "\ni:" << i << '\n';

    const int a = lowest_upshift_index(n, xs, i);
    // cout << "a:" << a << '\n';

    ans += (i - a) * xs[i] - (ss[i] - ss[a]);
    // cout << "1. ans:" << ans << '\n';

    if (a > 0) {
        const ll sz = a;
        ans += ss[a] + (n - xs[i]) * sz;
        // cout << "2. ans:" << ans << '\n';
    }

    const int b = highest_downshift_index(n, xs, i);
    // cout << "b:" << b << '\n';

    ans += ss[b + 1] - ss[i + 1] - (b - i) * xs[i];
    // cout << "3. ans:" << ans << '\n';

    const int w = xs.size();
    if (b < w - 1) {
        const ll sz = w - 1 - b;
        ans += sz * xs[i] + sz * n - (ss[w] - ss[b + 1]);
        // cout << "4. ans:" << ans << '\n';
    }

    return ans;
}

ll min_moves(const int n, const vector<ll> &xs) {
    const int w = xs.size();
    const auto ss = gather_partial_sums(xs);
    ll ans = 1e18;

    for (int i = 0; i < w; ++i) {
        ans = min(ans, moves_to(n, xs, ss, i));
    }

    return ans;
}

ll diff(const ll n, const ll x, const ll y) {
    const auto a = min(x, y);
    const auto b = max(x, y);
    return min(b - a, a + n - b);
}

ll bruteforce(const int n, const vector<ll> &xs) {
    ll ans = 1e18;

    for (const auto y : xs) {
        ll candidate = 0;
        for (const auto x : xs) {
            candidate += diff(n, x, y);
        }

        ans = min(ans, candidate);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int w, n;
        cin >> w >> n;
        vector<ll> xs(w, 0);
        for (auto &x : xs) {
            cin >> x;
            --x;
        }
        sort(begin(xs), end(xs));

        // cout << "Case #" << i << ": " << bruteforce(n, xs) << '\n';
        cout << "Case #" << i << ": " << min_moves(n, xs) << '\n';
    }

    return 0;
}
