#include <bits/stdc++.h>

using namespace std;

using i_t = unsigned long long;

i_t sector(const i_t n, const i_t m, const i_t sx, const i_t sy) {
    const bool inner = sx == 1;
    if (inner) return sy % (n / gcd(n, m));
    return sy % (m / gcd(n, m));
}

int main() {
    i_t n;
    i_t m;
    unsigned int q;

    cin >> n >> m >> q;

    for (unsigned int i = 0; i != q; ++i) {
        i_t sx;
        i_t sy;
        i_t ex;
        i_t ey;

        cin >> sx >> sy >> ex >> ey;

        cout << (sector(n, m, sx, sy) == sector(n, m, ex, ey) ? "YES" : "NO")
             << '\n';
    }
}
