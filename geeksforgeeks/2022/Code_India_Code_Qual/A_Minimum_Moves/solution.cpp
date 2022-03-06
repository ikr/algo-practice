#include <bitset>
#include <iostream>
using namespace std;
using ull = unsigned long long;

ull min_moves(const ull A, const ull B) {
    if (A >= B) return A - B;

    bitset<64> bits_A(A);
    bitset<64> bits_X(A ^ B);

    int orable{};
    for (int i = 0; i < 64; ++i) {
        if (bits_X[i] && !bits_A[i]) {
            ++orable;
            bits_X[i] = false;
        }
    }

    return bits_X.to_ullong() + (orable > 0 ? 1 : 0);
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
