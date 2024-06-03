#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const string Yes{"YES"};
static const string No{"NO"};
static const string Maybe{"MAYBE"};

string outcome(const int f, const int k, vector<int> xs) {
    const auto x0 = xs[f - 1];
    sort(rbegin(xs), rend(xs));

    const auto it = find(cbegin(xs), cend(xs), x0);
    const auto a = inof(it - cbegin(xs));

    const auto jt =
        find_if(it, cend(xs), [x0](const int x) { return x != x0; });
    const auto b = inof(jt - cbegin(xs)) - 1;

    if (b < k) return Yes;
    if (k <= a) return No;
    return Maybe;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, f, k;
        cin >> n >> f >> k;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << outcome(f, k, std::move(xs)) << '\n';
    }

    return 0;
}
