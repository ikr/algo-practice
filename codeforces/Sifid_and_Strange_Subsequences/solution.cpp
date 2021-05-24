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

static constexpr ll INF = 1e11;

int non_positive_num(const vi &xs) {
    return inof(
        count_if(cbegin(xs), cend(xs), [](const int x) { return x <= 0; }));
}

bool contains_a_positive(const vi &xs) {
    return any_of(cbegin(xs), cend(xs), [](const int x) { return x > 0; });
}

int min_positive(const vi &xs) {
    for (const auto x : xs) {
        if (x > 0) return x;
    }

    assert(false);
    return -1;
}

ll min_delta_of_non_positves(const vi &xs) {
    ll ans = INF;

    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] > 0) break;
        ans = min(ans, abs(llof(xs[i - 1] - xs[i])));
    }

    return ans;
}

int max_strange_subseq_length(const vi &xs) {
    const auto npn = non_positive_num(xs);
    if (contains_a_positive(xs)) {
        const auto delta = min_delta_of_non_positves(xs);
        const auto po = min_positive(xs);
        return (po <= delta) ? npn + 1 : npn;
    }

    return npn;
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
