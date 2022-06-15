#include <cassert>
#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const int A, const int B, const int C) {
    // cerr << "A:" << A << " B:" << B << " C:" << C << endl;
    if (A == B && B == C) return true;
    if (A % 2 == 0 && B % 2 == 0 && C % 2 == 0) return false;
    if (A % 2 == 1 && B % 2 == 1 && C % 2 == 1) return false;
    if (__builtin_popcount(A | B | C) == 1) {
        return (A & 1) + (B & 1) + (C & 1) == 2;
    }

    if ((A & 1) + (B & 1) + (C & 1) == 1) {
        if (A & 1) return is_possible((A + 1) >> 1, B >> 1, C >> 1);
        if (B & 1) return is_possible(A >> 1, (B + 1) >> 1, C >> 1);
        assert(C & 1);
        return is_possible(A >> 1, B >> 1, (C + 1) >> 1);
    }

    assert((A & 1) + (B & 1) + (C & 1) == 2);

    if ((A & 1) == 0) return is_possible((A + 1) >> 1, B >> 1, C >> 1);
    if ((B & 1) == 0) return is_possible(A >> 1, (B + 1) >> 1, C >> 1);
    assert((C & 1) == 0);
    return is_possible(A >> 1, B >> 1, (C + 1) >> 1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int A, B, C;
        cin >> A >> B >> C;

        cout << (is_possible(A, B, C) ? "YES" : "NO") << '\n';
    }

    return 0;
}
