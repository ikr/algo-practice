#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll Hi = 2LL * 100'000LL * 1'000'000'000LL;

vector<ll> precompure_squares() {
    vector<ll> result;
    for (ll i = 1; i * i <= Hi; ++i) result.push_back(i * i);
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto sqs = precompure_squares();

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<ll> xs(n);
        for (auto &x : xs) cin >> x;

        const auto total = accumulate(cbegin(xs), cend(xs), 0LL);
        cout << (ranges::binary_search(sqs, total) ? "YES" : "NO") << '\n';
    }

    return 0;
}
