#include <bits/stdc++.h>
using namespace std;

int solve(const int A, const int B) {
    if (__gcd(A, B) == 1) return B - A;

    const auto o1 = [&]() -> int {
        int a = A + 1;
        while (__gcd(a, B) != 1) ++a;
        return B - a;
    }();

    const auto o2 = [&]() -> int {
        int b = B - 1;
        while (__gcd(A, b) != 1) --b;
        return b - A;
    }();

    return max(o1, o2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int A, B;
    cin >> A >> B;

    cout << solve(A, B) << '\n';
    return 0;
}
