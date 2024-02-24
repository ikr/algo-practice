#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

struct Schedule final {
    int l;
    int d;
    int k;
    int c;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= M; ++i) {
        Schedule sch;
        cin >> sch.l >> sch.d >> sch.k >> sch.c;

        int a, b;
        cin >> a >> b;
        --a;
        --b;
    }

    return 0;
}
