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

priority_queue<int> freqs(const vi &xs) {
    map<int, int> m;
    for (const auto &x : xs) ++m[x];

    priority_queue<int> ans;
    for (const auto [_, v] : m) {
        ans.push(v);
    }
    return ans;
}

int min_moves(const vi &xs, const int k) {
    auto fs = freqs(xs);
    int ans = 0;
    int stash = 0;

    while (!fs.empty()) {
        assert(stash < k);
        const auto f = fs.top();
        fs.pop();

        if (f >= k) {
            assert(!stash);
            ++ans;
        } else {
            if (stash + f == k) {
                ++ans;
                stash = 0;
            } else if (stash + f < k) {
                stash += f;
            } else {
                assert(stash + f > k);
                const auto taking = k - stash;
                fs.push(f - taking);

                ++ans;
                stash = 0;
            }
        }
    }

    if (stash) ++ans;
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        cout << min_moves(xs, k) << '\n';
    }

    return 0;
}
