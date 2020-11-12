#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool straight(const int n, const int a, const int b) {
    assert(a <= b);
    return b - a <= a + n - b;
}

int lowest_upshift_index(const int n, const vector<ll> &xs, const int i) {
    assert(i >= 0);
    const int w = xs.size();
    assert(i < w);

    if (i == 0 || !straight(n, xs[i - 1], xs[i])) return -1;
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

    if (i == w - 1 || !straight(n, xs[i], xs[i + 1])) return -1;
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

    const int a = lowest_upshift_index(n, xs, i);
    if (a != -1) {
        const int sz = i - a;
        ans += sz * xs[i] - (ss[i] - ss[a]);
    }

    if (a > 0) {
        const int sz = a;
        ans += ss[a] + (n - xs[i]) * sz;
    }

    const int b = highest_downshift_index(n, xs, i);
    if (b != -1) {
        const int sz = b - i + 1;
        ans += ss[b + 1] - ss[i] - sz * xs[i];
    }

    const int w = xs.size();
    if (b > i && b < w - 1) {
        const int sz = w - b;
        ans += sz * xs[i] + sz * n - (ss[w] - ss[b]);
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

        cout << "Case #" << i << ": " << min_moves(n, xs) << '\n';
    }

    return 0;
}
