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

int non_positive_num(const vi &xs) {
    return count_if(cbegin(xs), cend(xs), [](const int x) { return x <= 0; });
}

vi set_of_positives(const vi &xs) {
    set<int> ans;
    for (const auto x : xs) {
        if (x > 0) ans.insert(x);
    }
    return vi(cbegin(ans), cend(ans));
}

vi sorted_gaps(const vi &xs) {
    vi ans(sz(xs));
    adjacent_difference(cbegin(xs), cend(xs), begin(ans));
    ans.erase(cbegin(ans));
    sort(begin(ans), end(ans));
    return ans;
}

int best_hi(const vi &gs, const vi &his) {
    auto it = lower_bound(cbegin(gs), cend(gs), his[0]);
    if (it == cend(gs)) return 0;

    auto record = *it;
    int ans = his[0];

    for (int i = 1; i < sz(his); ++i) {

    }

    return ans;
}

int max_strange_subseq_length(const vi &xs) {
    const auto gs = sorted_gaps(xs);
    const auto his = set_of_positives(xs);

    int ans = non_positive_num(xs);
    if (his.empty()) return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        sort(begin(xs), end(xs));
        cout << max_strange_subseq_length(xs) << '\n';
    }

    return 0;
}
