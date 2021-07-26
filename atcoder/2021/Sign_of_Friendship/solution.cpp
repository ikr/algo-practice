#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

double min_climb(const int D, const int H, const vector<pii> rs) {
    double ans = 0.0;

    for (const auto [d0, h0] : rs) {
        const double k = doof(H - h0) / doof(D - d0);
        const double h = h0 - k * d0;
        ans = max(ans, max(0.0, h));
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(4) << fixed;

    int N, D, H;
    cin >> N >> D >> H;

    vector<pii> rs;

    for (int i = 0; i < N; ++i) {
        int d, h;
        cin >> d >> h;

        if (d < D) rs.emplace_back(d, h);
    }

    cout << min_climb(D, H, rs) << '\n';

    return 0;
}
