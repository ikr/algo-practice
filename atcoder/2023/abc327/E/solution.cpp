#include <bits/stdc++.h>
using namespace std;

static constexpr double INF = 1e14;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr double one_contest_rating(const double p) { return p - 1200.0; }

double optimal_rating(const vector<int> &P) {
    const auto n = sz(P);

    vector<double> kds(n + 1, 0.0);
    kds[1] = 1.0;
    {
        double m = 1.0;
        for (int i = 2; i <= n; ++i) {
            m *= 0.9;
            kds[i] = kds[i - 1] + m;
        }
    }

    // D[j][k] is the maximum rating when choosing exactly k contests such that
    // their index in P is at most j.
    vector<vector<double>> D(n, vector<double>(n + 1, -INF));
    for (int j = 0; j < n; ++j) D[j][1] = one_contest_rating(P[j]);

    for (int j = 1; j < n; ++j) {
        for (int k = 2; k <= n; ++k) {
            D[j][k] = D[j - 1][k];

            auto R = (D[j - 1][k - 1] + (1200.0 / sqrt(k - 1.0))) * kds[k - 1];
            R *= 0.9;
            R += P[j];
            R /= kds[k];
            R -= 1200.0 / sqrt(k + 0.0);
            D[j][k] = max(D[j][k], R);
        }
    }

    double ans = -INF;
    for (const auto &row : D) {
        for (const auto x : row) ans = max(ans, x);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(7) << fixed;

    int N;
    cin >> N;

    vector<int> P(N);
    for (auto &p : P) cin >> p;

    cout << optimal_rating(P) << '\n';
    return 0;
}
