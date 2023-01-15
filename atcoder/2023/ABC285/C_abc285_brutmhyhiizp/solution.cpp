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

using ull = unsigned long long;

static constexpr int AZ = 26;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> exl_digits(const string &xs) {
    vector<int> result(sz(xs));
    transform(cbegin(xs), cend(xs), begin(result),
              [](const char a) { return inof(a) - 'A'; });
    cerr << result << endl;
    return result;
}

ull az_pow(const int exp) {
    ull result = 1;
    for (int i = 1; i <= exp; ++i) result *= AZ;
    return result;
}

ull value_of(const vector<int> &exl_ds) {
    if (sz(exl_ds) == 1) return exl_ds[0];

    ull result{};
    for (int i = 1; i < sz(exl_ds); ++i) result += az_pow(i);

    const auto recur = [&](const auto self, const vector<int> &ds) -> ull {
        if (sz(ds) == 1) return ds[0];
        ull ans{};
        ans += az_pow(sz(ds) - 1) * ds[0];
        ans += self(self, vector(cbegin(ds) + 1, cend(ds)));
        return ans;
    };

    result += recur(recur, exl_ds);
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    cerr << value_of(exl_digits(xs)) << endl;
    return 0;
}
