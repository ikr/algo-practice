#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool are_equal(const vector<string> &A, const vector<string> &B, const int dro,
               const int dco) {
    const auto H = sz(A);
    const auto W = sz(A[0]);
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            const auto a = A[(dro + ro) % H][(dco + co) % W];
            if (a != B[ro][co]) return false;
        }
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<string> A(H);
    for (auto &row : A) {
        cin >> row;
        assert(sz(row) == W);
    }

    vector<string> B(H);
    for (auto &row : B) {
        cin >> row;
        assert(sz(row) == W);
    }

    const auto ans = [&]() -> bool {
        for (int dro = 0; dro < H; ++dro) {
            for (int dco = 0; dco < W; ++dco) {
                if (are_equal(A, B, dro, dco)) return true;
            }
        }

        return false;
    }();

    cout << (ans ? "Yes" : "No") << '\n';
    return 0;
}
