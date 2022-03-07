#include <bitset>
#include <cassert>
#include <iostream>
using namespace std;
using ull = unsigned long long;

constexpr int BIT_MAX = 61;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

ull min_moves(const ull A, const ull B) {
    if (A >= B) return A - B;
    if ((A | B) == B) return 1;
    if (((A + 1) | B) == B) return 2;

    const auto hi = [&]() -> int {
        const bitset<BIT_MAX + 1> bits_a(A);
        const bitset<BIT_MAX + 1> bits_b(B);

        for (int i = BIT_MAX; i >= 0; --i) {
            if (bits_b[i] && !bits_a[i]) return i;
        }
        assert(false && "hi not found");
        return -1;
    }();

    const auto A_ = (A | ((1ULL << hi) - 1ULL)) + 1ULL;
    return A_ == B ? 2 : 3;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ull A, B;
        cin >> A >> B;
        cout << min_moves(A, B) << '\n';
    }

    return 0;
}
