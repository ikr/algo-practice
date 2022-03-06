#include <bitset>
#include <iostream>
using namespace std;
using ull = unsigned long long;

constexpr int BIT_MAX = 61;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

ull min_moves(const ull A, const ull B) {
    if (A >= B) return A - B;

    bitset<BIT_MAX + 1> bits_a(A);
    bitset<BIT_MAX + 1> bits_b(B);

    ull incs_num{};
    bool need_or = false;

    for (int i = 0; i <= BIT_MAX; ++i) {
        if (bits_b[i] && !bits_a[i]) {
            const auto o_xor_inc = [&]() -> ull {
                const ull mask = (1ULL << i) - 1ULL;
                return mask & (bits_a.to_ullong() ^ bits_b.to_ullong());
            }();

            const auto o_inc = [&]() -> ull {
                const ull mask = (1ULL << (i + 1)) - 1ULL;
                return (mask & bits_b.to_ullong()) -
                       (mask & bits_a.to_ullong());
            }();

            if (o_xor_inc < o_inc) {
                need_or = true;
                incs_num += o_xor_inc;

                bits_a[i] = true;
                for (int j = i - 1; j >= 0; --j) {
                    bits_b[j] = bits_a[j];
                }
            } else {
                incs_num += o_inc;

                for (int j = i; j >= 0; --j) {
                    bits_a[j] = bits_b[j];
                }
            }
        }
    }

    return incs_num + need_or;
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
