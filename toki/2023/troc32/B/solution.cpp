#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<int, int>> run_length_encode(const vector<int> &xs) {
    vector<pair<int, int>> ans{{xs[0], 1}};
    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] == ans.back().first) {
            ++(ans.back().second);
        } else {
            ans.emplace_back(xs[i], 1);
        }
    }
    return ans;
}

using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    auto rle = run_length_encode(xs);

    if (sz(rle) > 2 && sz(rle) % 2) {
        assert(rle[0].first == rle.back().first);
        const auto x = rle.back().second;
        rle.pop_back();
        rle[0].second += x;
    }

    ll ans{};
    for (const auto &[x, f] : rle) {
        if (x) ans += 1LL * f * (f + 1LL) / 2LL;
    }

    cout << ans << '\n';
    return 0;
}
