#include <bits/stdc++.h>
using namespace std;

static const string Pat{"wbwbwwbwbwbw"};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool exists(const string &haystack, const int W, const int B) {
    int w = 0;
    int b = 0;
    const int n = W + B;
    assert(sz(haystack) >= n);

    for (int i = 0; i < n; ++i) {
        if (haystack[i] == 'w') {
            ++w;
        } else {
            assert(haystack[i] == 'b');
            ++b;
        }
    }

    if (w == W && b == B) return true;

    for (int l = 1, r = n; r < sz(haystack); ++l, ++r) {
        if (haystack[l - 1] == 'w') {
            --w;
        } else {
            assert(haystack[l - 1] == 'b');
            --b;
        }

        if (haystack[r] == 'w') {
            ++w;
        } else {
            assert(haystack[r] == 'b');
            ++b;
        }
        if (w == W && b == B) return true;
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int W, B;
    cin >> W >> B;

    string buf = Pat;
    for (int i = 0; i < 500; ++i) {
        buf += Pat;
    }

    const auto yes = exists(buf, W, B);
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
