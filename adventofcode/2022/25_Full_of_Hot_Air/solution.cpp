#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

ll snafu_value_of_digit(const char x) {
    switch (x) {
    case '=':
        return -2;
    case '-':
        return -1;
    default:
        return inof(x) - inof('0');
    }
}

ll snafu_value(string s) {
    reverse(begin(s), end(s));
    ll m = 1;

    ll result{};
    for (const auto d : s) {
        result += snafu_value_of_digit(d) * m;
        m *= 5;
    }
    return result;
}

vector<ll> powers_of_5(const ll x) {
    vector<ll> result{1};
    ll m = 1;
    while (m * 5 <= x) {
        result.push_back(m * 5);
        m *= 5;
    }
    return result;
}

vector<int> snafu_digits_reversed(const ll x) {
    const auto ps = powers_of_5(x);
    cerr << "ps:" << ps << endl;
    vector<int> result(sz(ps), -2);

    const auto d0 = inof(x / ps.back());
    assert(1 <= d0 && d0 < 5);
    if (d0 > 2) {
        result.back() = d0 - 5;
        result.push_back(1);
    } else {
        result.back() = d0;
    }

    const auto carry = [&](const auto self, const int i) -> void {
        assert(i >= 0);
        assert(i <= sz(result));
        if (i == sz(result)) {
            result.push_back(1);
            return;
        }

        if (result[i] + 1 < 3) {
            ++result[i];
            return;
        }

        result[i] = (result[i] + 1) - 5;
        self(self, i + 1);
    };

    ll r = x;
    for (int i = sz(ps) - 1; i >= 0; --i) {
        const auto d = inof(r / ps[i]);
        assert(0 <= d && d < 5);

        if (d > 2) {
            result[i] = d - 5;
            carry(carry, i + 1);
        } else {
            result[i] = d;
        }

        r %= ps[i];
    }

    return result;
}

string snafu(const ll x) {
    const auto ds = snafu_digits_reversed(x);
    string result(sz(ds), '?');

    transform(cbegin(ds), cend(ds), begin(result), [](const int d) -> char {
        switch (d) {
        case -2:
            return '=';
        case -1:
            return '-';
        default:
            return static_cast<char>(inof('0') + d);
        }
    });

    reverse(begin(result), end(result));
    return result;
}

int main() {
    vector<string> xs;
    for (string line; getline(cin, line);) {
        xs.push_back(line);
    }

    vector<ll> ys(sz(xs));
    transform(cbegin(xs), cend(xs), begin(ys), snafu_value);

    const auto total = accumulate(cbegin(ys), cend(ys), 0LL, plus<ll>{});
    cerr << "total:" << total << endl;
    cout << snafu(total) << endl;
    return 0;
}
