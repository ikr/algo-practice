#include <bits/stdc++.h>
using namespace std;

double solve(const int a0, const int b0, const int c0) {
    // Probability of the state [a] [b] [c]
    vector<vector<vector<double>>> P(
        101, vector<vector<double>>(101, vector<double>(101, 0)));

    P[a0][b0][c0] = 1;

    for (int a = a0; a < 100; ++a) {
        for (int b = b0; b < 100; ++b) {
            for (int c = c0; c < 100; ++c) {
                P[a + 1][b][c] += a * P[a][b][c] / (a + b + c);
                P[a][b + 1][c] += b * P[a][b][c] / (a + b + c);
                P[a][b][c + 1] += c * P[a][b][c] / (a + b + c);
            }
        }
    }

    double ans = 0;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            ans += (100 + i + j - a0 - b0 - c0) *
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
