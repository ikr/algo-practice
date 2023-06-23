#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> digits(const string &s) {
    vector<int> xs(size(s));
    transform(cbegin(s), cend(s), begin(xs),
              [](const char x) -> int { return x - '0'; });
    return xs;
}

string bignum(const vector<int> &digits) {
    stringstream ss;
    for (const auto d : digits) ss << d;
    return ss.str();
}

int keep_last_digit(const ll x) { return inof(abs(x) % 10LL); }

int flawed_frequency_transmission_kth_digit(const int k, const vector<int> &xs,
                                            const vector<ll> &ss) {
    const auto sum = [&](const int i, const int j) -> ll {
        assert(i <= j);
        assert(0 <= i && i < sz(ss));
        assert(0 <= j && j < sz(ss));
        return ss[j] - (i ? ss[i - 1] : 0LL);
    };

    const auto block_size = k + 1;
    ll result{};

    for (int i = k; i < sz(xs); i += 4 * block_size) {
        result += sum(i, min(i + k, sz(xs) - 1));

        if (i + 2 * block_size < sz(xs)) {
            result -= sum(i + 2 * block_size,
                          min(i + k + 2 * block_size, sz(xs) - 1));
        }
    }

    return keep_last_digit(result);
}

vector<int> flawed_frequency_transmission(const vector<int> &xs) {
    vector<int> result(sz(xs));
    vector<ll> ss(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ss), plus<ll>{});

    for (int k = 0; k < sz(xs); ++k) {
        result[k] = flawed_frequency_transmission_kth_digit(k, xs, ss);
    }

    return result;
}

int main() {
    string s;
    cin >> s;

    string ss;
    for (int t = 1; t <= 10'000; ++t) {
        ss += s;
    }

    auto xs = digits(ss);
    for (int t = 1; t <= 100; ++t) {
        xs = flawed_frequency_transmission(xs);
        cerr << "Iteration " << t << " done" << endl;
    }

    const auto offset = stoi(s.substr(0, 7));
    cout << bignum(xs).substr(offset, 8) << '\n';
    return 0;
}
