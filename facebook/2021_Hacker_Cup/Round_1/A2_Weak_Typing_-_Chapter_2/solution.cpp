#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using Mint = atcoder::modint1000000007;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<bool> gather_milestones(const string &xs) {
    vector<bool> ans(sz(xs), false);
    optional<char> last_m;

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == 'F') continue;

        if (!last_m || *last_m != xs[i]) {
            last_m = xs[i];
            ans[i] = true;
        }
    }

    return ans;
}

struct Milestone final {
    int index;
    int span;
};

int solution(const string &xs) {
    const auto ms = gather_milestones(xs);

    optional<Milestone> pr = [&]() -> optional<Milestone> {
        if (!ms[0]) return nullopt;
        return Milestone{0, 1};
    }();

    Mint ss = 0;

    // dp[i] is the answer for all the sub-strings ending exactly at index i
    vector<Mint> dp(sz(xs), 0);

    for (int i = 1; i < sz(xs); ++i) {
        if (ms[i]) {
            if (pr) {
                ss += pr->span;
                pr = Milestone{i, i - pr->index};
                dp[i] = ss;
            } else {
                pr = Milestone{i, i + 1};
            }
        } else {
            dp[i] = dp[i - 1];
        }
    }

    return accumulate(cbegin(dp), cend(dp), Mint{0}).val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;

        string xs(n, ' ');
        cin >> xs;

        cout << "Case #" << i << ": " << solution(xs) << '\n';
    }

    return 0;
}
