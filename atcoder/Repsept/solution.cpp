#include <bits/stdc++.h>
using namespace std;

int solve(const int K) {
    for (int i = 1, sevens = 7 % K; i <= K;
         ++i, sevens = (sevens * 10 + 7) % K) {
        if (sevens == 0) return i;
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int K;
    cin >> K;
    cout << solve(K) << '\n';

    return 0;
}
