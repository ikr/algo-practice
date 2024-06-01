#include <bits/stdc++.h>
using namespace std;

int distanse_to_range(const pair<int, int> ab, const int x) {
    auto [a, b] = ab;
    if (a > b) swap(a, b);
    if (a <= x && x <= b) return 0;
    return min(abs(a - x), abs(b - x));
}

long long min_ops(const vector<int> &A, const vector<int> &B) {
    int gap{INT_MAX};
    long long result{};
    const auto tail = B.back();

    for (auto i = 0; i < ssize(A); ++i) {
        result += abs(A[i] - B[i]);
        gap = min(gap, distanse_to_range({A[i], B[i]}, tail));
    }

    return result + gap + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> A(n);
        for (auto &a : A) cin >> a;

        vector<int> B(n + 1);
        for (auto &b : B) cin >> b;

        cout << min_ops(A, B) << '\n';
    }

    return 0;
}
