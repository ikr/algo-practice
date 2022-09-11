#include <bits/stdc++.h>
using namespace std;

bool is_possible(const int K, vector<int> A, vector<int> B) {
    if (K == 0) return A == B;

    if (A.size() == 2) {
        if (A == B) {
            return K % 2 == 0;
        } else {
            return K % 2 == 1;
        }
    }

    if (A == B) return K != 1;

    const auto a0 = A[0];
    const auto i0 = distance(cbegin(B), find(cbegin(B), cend(B), a0));
    rotate(begin(B), begin(B) + i0, end(B));
    return A == B;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, K;
        cin >> N >> K;

        vector<int> A(N);
        for (auto &a : A) cin >> a;

        vector<int> B(N);
        for (auto &b : B) cin >> b;

        cout << "Case #" << i << ": "
             << (is_possible(K, move(A), move(B)) ? "YES" : "NO") << '\n';
    }

    return 0;
}
