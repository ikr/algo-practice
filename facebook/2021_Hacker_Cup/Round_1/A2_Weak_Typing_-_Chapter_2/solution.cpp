#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using Mint = atcoder::modint1000000007;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pii> gather_milestones(const string &xs) {
    vector<pii> ans;
    optional<int> pr;

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == 'F') continue;

        if (!pr) {
            pr = i;
            continue;
        }

        if (xs[*pr] != xs[i]) {
            ans.emplace_back(*pr, i);
            pr = i;
            continue;
        }

        pr = i;
    }

    return ans;
}

int solution(const string &xs) {
    Mint ans = 0;

    for (const auto [i, j]: gather_milestones(xs)) {
        const Mint a{i + 1};
        const Mint b{sz(xs) - j};
        ans += a * b;
    }

    return ans.val();
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
