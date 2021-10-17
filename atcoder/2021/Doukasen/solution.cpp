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

double meeting_time(const vector<pii> &ab) {
    double ans = 0.0;

    for (const auto [a, b] : ab) {
        ans += doof(a) / doof(b);
    }

    return ans / 2.0;
}

int containing_interval_index(const vector<pii> &ab, const double t) {
    double curr = 0;

    for (int i = 0; i < sz(ab); ++i) {
        const auto [a, b] = ab[i];
        if (t < curr + doof(a) / doof(b)) return i;
        curr += doof(a) / doof(b);
    }

    return sz(ab) - 1;
}

double meeting_point(const vector<pii> &ab) {
    const auto T = meeting_time(ab);
    const auto I = containing_interval_index(ab, T);

    double pre_x = 0;
    double pre_T = 0;
    for (int i = 0; i < I; ++i) {
        const auto [a, b] = ab[i];
        pre_T += doof(a) / doof(b);
        pre_x += a;
    }

    const double rest = T - pre_T;
    assert(rest >= 0.0);

    const double ratio = rest / (doof(ab[I].first) / doof(ab[I].second));
    return pre_x + ratio * doof(ab[I].first);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(6) << fixed;

    int n;
    cin >> n;

    vector<pii> ab(n);
    for (auto &[a, b] : ab) cin >> a >> b;

    cout << meeting_point(ab) << '\n';
    return 0;
}
