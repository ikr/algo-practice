#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<int, int> gather_freqs(const vi &xs) {
    map<int, int> ans;
    for (const auto x : xs) ++ans[x];
    return ans;
}

optional<pii> pair_up(map<int, int> &fs) {
    assert(!fs.empty());
    assert(sz(fs) > 1 || cbegin(fs)->second > 1);

    const auto a = cbegin(fs)->first;
    const auto b = sz(fs) == 1 ? cbegin(fs)->first : next(cbegin(fs))->first;

    if (abs(a - b) > 1) return nullopt;

    --fs[a];
    --fs[b];

    if (!fs[a]) fs.erase(a);
    if (b != a && !fs[b]) fs.erase(b);

    return pii{a, b};
}

bool can_reduce_to_single(map<int, int> fs) {
    map<int, int> fs_;

    while (sz(fs) > 1 || cbegin(fs)->second > 1) {
        while (!fs.empty()) {
            const auto ab = pair_up(fs);
            if (!ab) return false;

            const auto [a, b] = *ab;
            ++fs_[a + b];
        }

        swap(fs, fs_);
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(1 << n);
        for (auto &x : xs) cin >> x;

        const auto ans = can_reduce_to_single(gather_freqs(xs));
        cout << (ans ? "YES" : "NO") << '\n';
    }

    return 0;
}
