#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N, A, B, P, Q, R, S;
    cin >> N >> A >> B >> P >> Q >> R >> S;

    --A;
    --B;
    --P;
    --Q;
    --R;
    --S;

    const int H = inof(Q - P + 1);
    const int W = inof(S - R + 1);

    vector<string> grid(H, string(W, '.'));

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            const ll gro = P + ro;
            const ll gco = R + co;

            if (gro - A == gco - B || gro - A == B - gco) {
                grid[ro][co] = '#';
            }
        }
    }

    for (const auto &row : grid) {
        cout << row << '\n';
    }
    return 0;
}
