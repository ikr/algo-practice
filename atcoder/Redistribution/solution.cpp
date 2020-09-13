#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll M = 1e9 + 7;
constexpr ll S_MAX = 2000;

int solve(const int s) {
    vector<vector<int>>(S_MAX + 1, vector<int>(S_MAX + 1, 0));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int s;
    cin >> s;
    cout << solve(s) << '\n';

    return 0;
}
