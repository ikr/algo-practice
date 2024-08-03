#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool beats(const char a, const char b) {
    switch (a) {
    case 'R':
        return b == 'S';
    case 'P':
        return b == 'R';
    case 'S':
        return b == 'P';
    default:
        assert(false && "/o\\");
        return false;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    string xs;
    cin >> xs;
    assert(sz(xs) == n);

    map<char, vector<int>> D{
        {'R', vector(n, 0)}, {'P', vector(n, 0)}, {'S', vector(n, 0)}};

    D['R'][0] = beats('R', xs[0]);
    D['P'][0] = beats('P', xs[0]);
    D['S'][0] = beats('S', xs[0]);

    for (int i = 1; i < n; ++i) {
        for (const auto a : {'R', 'P', 'S'}) {
            for (const auto a_ : {'R', 'P', 'S'}) {
                if (a_ == a) continue;
                if (!beats(xs[i], a)) D[a][i] = max(D[a][i], D[a_][i - 1]);
                if (beats(a, xs[i])) D[a][i] = max(D[a][i], D[a_][i - 1] + 1);
            }
        }
    }

    cout << max({D['R'].back(), D['P'].back(), D['S'].back()}) << '\n';
    return 0;
}
