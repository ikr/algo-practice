#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <optional>
#include <set>
#include <vector>
using namespace std;
using ll = long long;
using vi = vector<int>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

optional<vi> alans_subset(const int N, const ll X, const ll Y) {
    const ll T = llof(N) * llof(N + 1) / 2LL;
    const ll P = X * T;
    const ll Q = X + Y;
    if (P % Q != 0LL) return nullopt;
    const ll S = P / Q;

    if (S <= N) return vi{inof(S)};

    int s = S;
    vi result;
    set<int> src;
    for (int i = 1; i <= N; ++i) src.insert(i);

    while (!src.empty() && *crbegin(src) < s) {
        s -= *crbegin(src);
        result.push_back(*crbegin(src));

        src.erase(prev(cend(src)));
    }

    if (src.empty()) return nullopt;
    result.push_back(s);
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, X, Y;
        cin >> N >> X >> Y;

        const auto ans = alans_subset(N, X, Y);
        cout << "Case #" << i << ": " << (ans ? "POSSIBLE" : "IMPOSSIBLE")
             << '\n';
        if (ans) cout << sz(*ans) << '\n' << *ans << '\n';
    }

    return 0;
}
