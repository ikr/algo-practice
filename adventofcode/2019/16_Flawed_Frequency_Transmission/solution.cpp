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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const vector BasePattern{0, 1, 0, -1};

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

int keep_last_digit(const long long x) { return inof(abs(x) % 10LL); }

int flawed_frequency_transmission_kth_digit(const vector<int> &pat, const int k,
                                            const vector<int> &xs) {
    assert(0 <= k && k < sz(xs));
    const auto rep = k + 1;
    const auto block_size = sz(pat) * rep;
    const auto block0_size = block_size - 1;

    vector<int> M(sz(xs));
    iota(begin(M), end(M), 0);

    transform(cbegin(M), cend(M), begin(M), [&](const int i) -> int {
        if (i < block0_size) {
            const auto j = (i + 1) / rep;
            assert(j < sz(pat));
            return pat[j];
        }

        const auto j = ((i - block0_size + 1) % block_size) / rep;
        assert(j < sz(pat));
        return pat[j];
    });

    cerr << "M: " << M << endl;

    return keep_last_digit(transform_reduce(
        cbegin(xs), cend(xs), cbegin(M), 0LL, plus<long long>{},
        [](const int a, const int b) -> long long { return 1LL * a * b; }));
}

vector<int> flawed_frequency_transmission(const vector<int> &pat,
                                          const vector<int> &xs) {
    vector<int> result(sz(xs));
    iota(begin(result), end(result), 0);
    transform(cbegin(result), cend(result), begin(result), [&](const int k) {
        return flawed_frequency_transmission_kth_digit(pat, k, xs);
    });
    return result;
}

int main() {
    string s;
    cin >> s;

    cout << flawed_frequency_transmission_kth_digit(BasePattern, 0,
                                                    digits("12345678"))
         << '\n';

    return 0;
}
