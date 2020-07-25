#include <bits/stdc++.h>
using namespace std;

int muls_to_exceed(const int a, int b) {
    int ans = 0;

    while (b <= a) {
        b *= 2;
        ++ans;
    }

    return ans;
}

bool solve(const int A, int B, const int C, int K) {
    const int one = muls_to_exceed(A, B);
    K -= one;
    if (K < 0) return false;

    for (int i = 0; i < one; ++i) B *= 2;
    return K >= muls_to_exceed(B, C);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int A, B, C, K;
    cin >> A >> B >> C >> K;

    cout << (solve(A, B, C, K) ? "Yes" : "No") << "\n";

    return 0;
}
