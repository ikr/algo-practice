#include <atcoder/lazysegtree>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll e() { return 0; }
constexpr ll z() { return 0; }
constexpr ll mmax(const ll x, const ll y) { return max(x, y); }
constexpr ll mplus(const ll x, const ll y) { return x + y; }

int find_limit(const vector<pair<int, int>> &spans) {
    int ans = -1;

    for (const auto s : spans) {
        ans = max(ans, s.second);
    }

    return ans;
}

bool can_do_it(const vector<pair<int, int>> &spans, const vector<int> &util,
               const ll w) {
    const int lim = find_limit(spans);
    atcoder::lazy_segtree<ll, mmax, e, ll, mplus, mplus, z> tree(lim);

    const int n = spans.size();
    for (int i = 0; i < n; ++i) {
        tree.apply(spans[i].first, spans[i].second, util[i]);
    }

    const ll top = tree.all_prod();
    return top <= w;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, w;
    cin >> n >> w;
    vector<pair<int, int>> spans(n, {0, 0});
    vector<int> util(n, 0);

    for (int i = 0; i < n; ++i) {
        cin >> spans[i].first >> spans[i].second >> util[i];
    }

    cout << (can_do_it(spans, util, w) ? "Yes\n" : "No\n");

    return 0;
}
