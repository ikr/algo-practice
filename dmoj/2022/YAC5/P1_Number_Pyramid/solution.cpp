#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

using ll = long long;

static ll mod = 0;

// https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/ModularArithmetic.h
namespace kactl {
struct Mod {
    ll x;
    Mod(ll xx) : x(xx) {}
    Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
    Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
    Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
    Mod operator^(ll e) {
        if (!e) return Mod(1);
        Mod r = *this ^ (e / 2);
        r = r * r;
        return e & 1 ? *this * r : r;
    }
};
} // namespace kactl

ostream &operator<<(ostream &os, const kactl::Mod &box) {
    os << box.x;
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<kactl::Mod> optimal_bottom_row(const int N, const int X) {
    vector<kactl::Mod> src(N, 0);
    src.back() = mod - 1LL;

    for (int i = sz(src) - 2; i >= 0; --i) {
        src[i] = src[i + 1] + src[i + 1];
    }

    auto delta = src[0] - kactl::Mod{X};

    for (int i = 0; i < sz(src) - 1; ++i) {
        src[i] = src[i] - delta;

        auto x = src[i];
        auto x_ = src[i + 1] + src[i + 1];
        delta = x_ - x;
    }

    vector<kactl::Mod> result(N, mod - 1);
    result.back() = src.back() - delta;
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, X;
    cin >> N >> mod >> X;

    cout << optimal_bottom_row(N, X) << '\n';
    return 0;
}
