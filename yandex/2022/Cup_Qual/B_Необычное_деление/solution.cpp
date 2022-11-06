#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> vector<int> digits_reversed(T n) {
    vector<int> ans;

    while (n) {
        ans.push_back(inof(n % static_cast<T>(10)));
        n /= static_cast<T>(10);
    }

    return ans;
}

template <typename T> vector<int> digits(T n) {
    auto ans = digits_reversed(n);
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

void remove_leading_zeros(vector<int> &ds) {
    for (auto it = ds.begin(); it != ds.end();) {
        if (*it != 0) break;
        it = ds.erase(it);
    }
}

constexpr int bbase(const int b) {
    switch (b) {
    case 2:
        return 5;
    case 3:
        return 4;
    case 4:
        return 3;
    default:
        return 2;
    }
}

vector<int> closest_to_n_in_bbase(const ll n, const int b) {
    const auto ds = digits(n);
    vector<int> result(sz(ds), bbase(b) - 1);

    for (int i = 0; i < sz(ds); ++i) {
        if (ds[i] % b == 0) {
            result[i] = (ds[i] / b);
            continue;
        }

        if (ds[i] < b) {
            result[i] = 0;
            break;
        }

        int q = 0;
        while ((q + 1) * b < ds[i]) ++q;
        result[i] = q;
        break;
    }

    return result;
}

ll ipow(const int b, const int e) {
    ll result{1};
    for (int i = 1; i <= e; ++i) {
        result *= b;
    }
    return result;
}

ll num_matches(const ll n, const int b) {
    if (b == 1) return n;
    if (n < b) return 0LL;

    auto ds = closest_to_n_in_bbase(n, b);
    reverse(begin(ds), end(ds));

    ll result{};
    ll mul = 1;
    for (const auto d : ds) {
        result += d * mul;
        mul *= bbase(b);
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        int b;
        cin >> n >> b;

        cout << num_matches(n, b) << '\n';
    }

    return 0;
}
