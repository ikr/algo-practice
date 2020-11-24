#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

double solve(const int a0, const int b0, const int c0) {
    vector<vector<vector<double>>> P(
        101, vector<vector<double>>(101, vector<double>(101, 0)));

    P[a0][b0][c0] = 1;

    for (int a = a0; a <= (a0 ? 100 : 0); ++a) {
        for (int b = b0; b <= (b0 ? 100 : 0); ++b) {
            for (int c = c0; c <= (c0 ? 100 : 0); ++c) {
                if (a == a0 && b == b0 && c == c0) continue;

                if (a) {
                    P[a][b][c] += (a - 1) * P[a - 1][b][c];
                }

                if (b) {
                    P[a][b][c] += (b - 1) * P[a][b - 1][c];
                }

                if (c) {
                    P[a][b][c] += (c - 1) * P[a][b][c - 1];
                }

                P[a][b][c] /= doof(a + b + c - 1);
            }
        }
    }

    double ans = 0;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            ans += doof(100 + i + j - a0 - b0 - c0) *
                   (P[100][i][j] + P[i][100][j] + P[i][j][100]);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(7) << fixed;

    int a0, b0, c0;
    cin >> a0 >> b0 >> c0;
    cout << solve(a0, b0, c0) << '\n';

    return 0;
}
