#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi dots_psums(const string &s) {
    vi ans(sz(s), 0);
    int curr = 0;

    for (int i = 0; i < sz(s); ++i) {
        if (s[i] == '.') {
            ++curr;
        }

        ans[i] = curr;
    }

    return ans;
}

int longest_conseq_xs(const string &s, const int k) {
    const auto ps = dots_psums(s);
    const auto num_dots = [&ps](const int l, const int r) -> int {
        return ps[min(r - 1, sz(ps) - 1)] - (l ? ps[l - 1] : 0);
    };

    int ans{};

    for (int i = 0; i < sz(s); ++i) {
        if (!k && s[i] == '.') continue;

        int lo = min(i + max(k, 1), sz(s));
        assert(num_dots(i, lo) <= k);
        int hi = sz(s);

        if (num_dots(i, hi) <= k) {
            ans = max(ans, hi - i);
            break;
        }

        while (lo + 1 < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (num_dots(i, mid) <= k) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        ans = max(ans, lo - i);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s;
    cin >> s;

    int k;
    cin >> k;

    cout << longest_conseq_xs(s, k) << '\n';
    return 0;
}
