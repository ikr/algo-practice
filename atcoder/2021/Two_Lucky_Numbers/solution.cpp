#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> vi digits_reversed(T n) {
    vi ans;

    while (n) {
        ans.push_back(inof(n % static_cast<T>(10)));
        n /= 10;
    }

    return ans;
}

template <typename T> vi digits(T n) {
    vi ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

template <typename T> T number(const vector<int> &ds) {
    if (ds.empty()) return 0;

    T ans = 0;
    T mul = 1;
    for (auto it = ds.crbegin(); it != ds.crend(); ++it) {
        ans += (*it) * mul;
        mul *= static_cast<T>(10);
    }
    return ans;
}

ll find_x(const ll A, const ll B) {
    auto db = B == 1 ? vi{1, 0} : digits(B);
    const auto da = digits(2 * A);
    db.insert(cend(db), cbegin(da), cend(da));
    return number<ll>(db) / 2LL;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll A, B;
    cin >> A >> B;
    cout << find_x(A, B) << '\n';
    return 0;
}
