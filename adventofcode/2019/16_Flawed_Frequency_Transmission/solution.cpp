#include <bits/stdc++.h>
using namespace std;

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

int keep_last_digit(const long long x) { return inof(abs(x) % 10LL); }

int flawed_frequency_transmission_kth_digit(const int k,
                                            const vector<int> &xs) {
    assert(0 <= k && k < sz(xs));
    const auto block_size = 4 * (k + 1);
    long long result{};

    for (int i = k; i < sz(xs); i += 4 * block_size) {
        for (int j = 0; j < block_size; ++j) {
            if (i + j < sz(xs)) {
                result += xs[i + j];
            }
            if (i + j + 2 * block_size < sz(xs)) {
                result -= xs[i + j + 2 * block_size];
            }
        }
    }

    return keep_last_digit(result);
}

vector<int> flawed_frequency_transmission(const vector<int> &xs) {
    vector<int> result(sz(xs));
    iota(begin(result), end(result), 0);
    transform(cbegin(result), cend(result), begin(result), [&](const int k) {
        if (k % 1000 == 0) cerr << "digit " << k << endl;
        return flawed_frequency_transmission_kth_digit(k, xs);
    });
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
    cerr << "xs ready" << endl;
    for (int t = 1; t <= 1; ++t) {
        xs = flawed_frequency_transmission(xs);
        cerr << "Iteration " << t << " done" << endl;
    }

    const auto offset = stoi(s.substr(0, 7));

    cout << bignum(xs).substr(offset, 8) << '\n';
    return 0;
}
