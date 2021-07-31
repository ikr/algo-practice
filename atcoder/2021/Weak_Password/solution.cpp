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

constexpr bool are_conseq(const int x, const int y) {
    return (x + 1) % 10 == y;
}

bool is_weak(const array<int, 4> &xs) {
    const set<int> xss(cbegin(xs), cend(xs));
    if (sz(xss) == 1) return true;

    int conseq_num = 0;
    for (int i = 0; i < 3; ++i) {
        if (are_conseq(xs[i], xs[i + 1])) {
            ++conseq_num;
        }
    }

    return conseq_num == 3;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    string xs;
    cin >> xs;

    array<int, 4> ys;
    for (int i = 0; i < 4; ++i) {
        ys[i] = inof(xs[i] - '0');
    }

    const bool w = is_weak(ys);
    cout << (w ? "Weak" : "Strong") << '\n';

    return 0;
}
