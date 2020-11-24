#include <bits/stdc++.h>
using namespace std;

double solve(const int a0, const int b0, const int c0) {
    // Probability of the state [a] [b] [c]
    vector<vector<vector<double>>> P(
        101, vector<vector<double>>(101, vector<double>(101, 0)));

    P[a0][b0][c0] = 1;

    for (int a = a0; a <= (a0 ? 100 : 0); ++a) {
        for (int b = b0; b <= (b0 ? 100 : 0); ++b) {
            for (int c = c0; c <= (c0 ? 100 : 0); ++c) {
                if (a == a0 && b == b0 && c == c0) continue;

                if (a > a0) {
                    P[a][b][c] += (a - 1) * P[a - 1][b][c];
                }

                if (b > b0) {
                    P[a][b][c] += (b - 1) * P[a][b - 1][c];
                }

                if (c > c0) {
                    P[a][b][c] += (c - 1) * P[a][b][c - 1];
                }

                P[a][b][c] /= (a + b + c - 1);
            }
        }
    }

    // -----
    vector<vector<vector<double>>> p(
        101, vector<vector<double>>(101, vector<double>(101, 0)));
    p[a0][b0][c0] = 1;
    for (int i = a0; i < 100; i++) {
        for (int j = b0; j < 100; j++) {
            for (int k = c0; k < 100; k++) {
                double ip = double(i) / (i + j + k);
                double jp = double(j) / (i + j + k);
                double kp = double(k) / (i + j + k);

                p[i + 1][j][k] += p[i][j][k] * ip;
                p[i][j + 1][k] += p[i][j][k] * jp;
                p[i][j][k + 1] += p[i][j][k] * kp;
            }
        }
    }

    const auto eq = [](const double x, const double y) {
        return abs(x - y) < 0.0000001;
    };

    for (int a = 0; a < 101; ++a) {
        for (int b = 0; b < 101; ++b) {
            for (int c = 0; c < 101; ++c) {
                if (!eq(p[a][b][c], P[a][b][c])) {
                    if ((a == 100) + (b == 100) + (c == 100) > 1) continue;

                    cout << "Failed on a:" << a << " b:" << b << "c:" << c
                         << endl;

                    cout << "lhs:" << p[a][b][c] << " rhs:" << P[a][b][c]
                         << endl;
                }

                //assert(eq(p[a][b][c], P[a][b][c]));
            }
        }
    }
    // -----

    double ans = 0;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            ans += (100 + i + j - a0 - b0 - c0) *
                   (p[100][i][j] + p[i][100][j] + p[i][j][100]);
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
