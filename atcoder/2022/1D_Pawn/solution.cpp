#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, K, Q;
    cin >> N >> K >> Q;

    vector<int> A(K);
    for (auto &a : A) cin >> a;

    for (int i = 1; i <= Q; ++i) {
        int L;
        cin >> L;
        --L;

        if (L == sz(A) - 1) {
            if (A[L] < N) ++A[L];
            continue;
        }

        if (A[L] + 1 < A[L + 1]) ++A[L];
    }

    for (auto i = A.cbegin(); i != A.cend(); ++i) {
        if (i != A.cbegin()) cout << ' ';
        cout << *i;
    }
    cout << '\n';
    return 0;
}
