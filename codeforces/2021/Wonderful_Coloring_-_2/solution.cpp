#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

map<int, int> freqs(const vi &xs) {
    map<int, int> fs;
    for (const auto x : xs) ++fs[x];
    return fs;
}

vi paint_batch(const int k, map<int, int> &fs, priority_queue<pii> &pq) {
    vi ans;
    ans.reserve(k);
    int i = k;

    while (!pq.empty() && i > 0) {
        const auto [v, x] = pq.top();
        pq.pop();

        for (int j = 0; j < min(i, v); ++j) {
            ans.push_back(x);
        }

        fs.erase(x);
        i -= min(i, v);
    }

    if ((sz(ans) < k)) return {};
    return ans;
}

multimap<int, int> indices_by_value(const vi &xs) {
    multimap<int, int> ans;

    for (int i = 0; i < sz(xs); ++i) {
        ans.emplace(xs[i], i);
    }

    return ans;
}

vi coloring(const vi &xs, const int k) {
    auto fs = freqs(xs);
    priority_queue<pii> pq;

    for (const auto [x, v] : fs) {
        pq.emplace(v, x);
    }

    vector<pii> corr;
    corr.reserve(sz(xs) / 2);

    for (;;) {
        const auto p = paint_batch(k, fs, pq);
        if (p.empty()) break;
        assert(sz(p) == k);

        for (int i = 0; i < sz(p); ++i) {
            corr.emplace_back(p[i], i + 1);
        }
    }

    vi ans(sz(xs), 0);
    auto idx = indices_by_value(xs);
    for (const auto [x, c] : corr) {
        const auto it = idx.find(x);
        assert(it != cend(idx));

        ans[it->second] = c;
        idx.erase(it);
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

        vi xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << coloring(xs, k) << '\n';
    }

    return 0;
}
