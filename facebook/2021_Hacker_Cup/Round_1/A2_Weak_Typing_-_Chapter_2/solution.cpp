#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using Mint = atcoder::modint1000000007;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

ostream &operator<<(ostream &os, const Mint x) {
    os << x.val();
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<bool> gather_milestones(const string &xs) {
    vector<bool> ans(sz(xs), false);

    const auto it =
        find_if(cbegin(xs), cend(xs), [](const char x) { return x != 'F'; });

    if (it == cend(xs)) return ans;

    const auto jt = find_if(next(it), cend(xs), [&](const char x) {
        return (x != 'F') && (x != *it);
    });

    if (jt == cend(xs)) return ans;

    const int i0 = inof(xs.rfind(*it, distance(cbegin(xs), jt)));

    ans[i0] = true;
    char last_m = xs[i0];

    for (int i = i0 + 1; i < sz(xs); ++i) {
        if (xs[i] == 'F') continue;

        if (last_m != xs[i]) {
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
    Mint curr = 0;

    // dp[i] is the answer for all the sub-strings ending exactly at index i
    vector<Mint> dp(sz(xs), 0);

    for (int i = 1; i < sz(xs); ++i) {
        if (ms[i]) {
            if (pr) {
                ss += pr->span;
                curr += ss;
                dp[i] = curr;

                pr = Milestone{i, i - pr->index};
            } else {
                pr = Milestone{i, i + 1};
            }
        } else {
            dp[i] = dp[i - 1];
        }
    }

    cerr << dp << endl;

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
