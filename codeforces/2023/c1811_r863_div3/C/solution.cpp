#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> recover_A(const vector<int> &B) {
    const auto n = sz(B) + 1;
    assert(n >= 2);
    vector<int> A(n, -1);

    for (int i = 0; i < sz(B); ++i) {
        if (A[i] == -1) {
            A[i] = B[i];

            if (i < sz(B) - 1 && B[i] < B[i + 1]) {
                A[i + 1] = B[i];
            }

            continue;
        }

        if (i < sz(B) - 1 && B[i] < B[i + 1]) {
            A[i + 1] = B[i];
        }
    }

    if (A.back() == -1) A.back() = B.back();

    // for (int i = 0; i < sz(B); ++i) {
    //     if (B[i] != max(A[i], A[i + 1])) {
    //         cerr << "Failed on [" << A << "] → [" << B << "]" << endl;
    //     }
    // }

    return A;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> B(n - 1);
        for (auto &b : B) cin >> b;

        cout << recover_A(B) << '\n';
    }

    return 0;
}
