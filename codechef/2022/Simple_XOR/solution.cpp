#include <array>
#include <cassert>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>
using namespace std;

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<ll, ll> first_z_indeices(const ll x) {
    vector<ll> result;

    for (ll i = 0; i < 33LL; ++i) {
        if (!((1LL << i) & x)) {
            result.push_back(i);
            if (sz(result) == 2) break;
        }
    }

    assert(sz(result) == 2);
    return {result[0], result[1]};
}

optional<array<ll, 4>> find_quad(const ll L, const ll R) {
    array<ll, 4> result{};
    result[0] = L;

    const auto [i, j] = first_z_indeices(L);
    result[1] = result[0] | (1LL << i);
    if (result[1] >= R) return nullopt;

    result[2] = result[0] | (1LL << j);
    if (result[2] >= R) return nullopt;

    result[3] = result[0] | (1LL << i) | (1LL << j);
    if (result[3] >= R) return nullopt;

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll L, R;
        cin >> L >> R;

        const auto ans = find_quad(L, R);
        if (ans) {
            cout << *ans << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}
