#include <cassert>
#include <iostream>
#include <string>
using namespace std;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

string spect_seq(int r, int b) {
    string result;
    const auto span = r / (b + 1);
    int extra = r % (b + 1);

    while (r || b) {
        if (r) {
            const auto d = [&]() -> int {
                if (r <= span) return r;

                if (extra) {
                    --extra;
                    return span + 1;
                }

                return span;
            }();

            result += string(d, 'R');
            r -= d;
        }

        if (b) {
            result += 'B';
            --b;
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, r, b;
        cin >> n >> r >> b;
        assert(r + b == n);
        assert(b < r);
        cout << spect_seq(r, b) << '\n';
    }

    return 0;
}
