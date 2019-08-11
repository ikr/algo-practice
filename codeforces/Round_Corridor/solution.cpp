#include <bits/stdc++.h>

using namespace std;

using i_t = unsigned long long;

int main() {
    i_t n;
    i_t m;
    unsigned int q;

    cin >> n >> m >> q;

    vector<i_t> ib(n);
    for (i_t i = 0; i != n; ++i) {
        ib[i] = i * (lcm(n, m) / n);
    }

    vector<i_t> ob(m);
    for (i_t i = 0; i != m; ++i) {
        ob[i] = i * (lcm(n, m) / m);
    }

    for (unsigned int i = 0; i != q; ++i) {
        i_t sx;
        i_t sy;
        i_t ex;
        i_t ey;

        cin >> sx >> sy >> ex >> ey;
    }
}
