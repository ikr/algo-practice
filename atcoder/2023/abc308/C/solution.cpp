#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

pll simplify(const pll &xy) {
    const auto [x, y] = xy;
    const auto g = gcd(x, y);
    return {x / g, y / g};
}

struct Element final {
    pll rate;
    int index;
};

double estimate(const pll &ab) {
    const auto [a, b] = ab;
    return static_cast<double>(a) / static_cast<double>(b);
}

struct ElementLess final {
    bool operator()(const Element &a, const Element &b) const {
        if (a.rate == b.rate) return a.index < b.index;
        return estimate(a.rate) > estimate(b.rate);
    }
};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<Element> xs;
    xs.reserve(N);

    for (int i = 1; i <= N; ++i) {
        ll a, b;
        cin >> a >> b;
        xs.push_back(Element({simplify({a, a + b}), i}));
    }

    sort(begin(xs), end(xs), ElementLess{});

    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) cout << ' ';
        cout << i->index;
    }
    cout << '\n';

    return 0;
}
