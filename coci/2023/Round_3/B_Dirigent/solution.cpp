#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> indicies(const vector<int> &xs) {
    vector<int> result(sz(xs));
    for (int i = 0; i < sz(xs); ++i) result[xs[i]] = i;
    return result;
}

vector<bool> solve(vector<int> xs, const vector<pii> &ops) {
    const auto n = sz(xs);
    vector<bool> ans;
    ans.reserve(n);
    const auto mod_n = [n](const int x) -> int { return ((x % n) + n) % n; };

    auto idx = indicies(xs);
    set<int> bad;
    for (int a = 0; a < n; ++a) {
        const auto i = idx[a];
        const auto j = mod_n(i + 1);
        if (xs[j] != mod_n(a + 1)) bad.insert(a);
    }

    for (const auto &[a, b] : ops) {
        const auto i = idx[a];
        const auto j = idx[b];
        swap(xs[i], xs[j]);
        swap(idx[a], idx[b]);

        {
            const auto _i = mod_n(i - 1);
            if (mod_n(xs[_i] + 1) == xs[i]) {
                bad.erase(xs[_i]);
            } else {
                bad.insert(xs[_i]);
            }
            const auto i_ = mod_n(i + 1);
            if (mod_n(xs[i] + 1) == xs[i_]) {
                bad.erase(xs[i]);
            } else {
                bad.insert(xs[i]);
            }
        }

        {
            const auto _j = mod_n(j - 1);
            if (mod_n(xs[_j] + 1) == xs[j]) {
                bad.erase(xs[_j]);
            } else {
                bad.insert(xs[_j]);
            }
            const auto j_ = mod_n(j + 1);
            if (mod_n(xs[j] + 1) == xs[j_]) {
                bad.erase(xs[j]);
            } else {
                bad.insert(xs[j]);
            }
        }

        ans.push_back(bad.empty());
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q;
    cin >> n >> q;

    vector<int> xs(n);
    for (auto &x : xs) {
        cin >> x;
        --x;
    }

    vector<pii> ops(q);
    for (auto &[a, b] : ops) {
        cin >> a >> b;
        --a;
        --b;
    }

    for (const auto yes : solve(move(xs), ops)) {
        cout << (yes ? "DA" : "NE") << '\n';
    }
    return 0;
}
