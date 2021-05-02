#include <bits/stdc++.h>
#include <climits>
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

double min_climb_for_upper(const int D, const int H, const int h0,
                           const vector<pii> rs) {
    int d0 = INT_MAX;
    for (const auto [d, h] : rs) {
        if (h0 == h) {
            d0 = min(d0, d);
        }
    }

    assert(d0 != INT_MAX);

    double ans = doof(D * h0 - d0 * H) / doof(D - d0);
    return ans < 0.0 ? 0.0 : ans;
}

double min_climb_for_lower(const int D, const int H, const int h0,
                           const vector<pii> rs) {
    int d0 = 0;
    for (const auto [d, h] : rs) {
        if (h0 == h) {
            d0 = max(d0, d);
        }
    }

    assert(d0 != INT_MAX);

    return doof(D * (h0 - H)) / doof(D - d0) + doof(H);
}

double min_climb(const int D, const int H, int h0, const vector<pii> rs) {
    if (rs.empty()) return 0;
    if (h0 == H) return h0;

    return h0 < H ? min_climb_for_upper(D, H, h0, rs)
                  : min_climb_for_lower(D, H, h0, rs);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(4) << fixed;

    int N, D, H;
    cin >> N >> D >> H;

    vector<pii> rs;

    int h0 = 0;

    for (int i = 0; i < N; ++i) {
        int d, h;
        cin >> d >> h;

        if (d < D) {
            rs.emplace_back(d, h);
            h0 = max(h0, h);
        }
    }

    cout << min_climb(D, H, h0, rs) << '\n';

    return 0;
}
