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

template <typename T>
bool is_at(const vector<T> &haystack, const vector<T> &needle, const int i) {
    for (int j = 0; j < sz(needle); ++j) {
        if (haystack[i + j] != needle[j]) return false;
    }

    return true;
}

template <typename T> int tail_period(const vector<T> &xs) {
    const auto marker_size = 20;
    const vector marker(cend(xs) - marker_size, cend(xs));
    assert(is_at(xs, marker, sz(xs) - marker_size));

    for (int i = sz(xs) - marker_size - 1; i >= 0; --i) {
        if (is_at(xs, marker, i)) {
            return sz(xs) - marker_size - i;
        }
    }

    return -1;
}

int flawed_frequency_transmission_kth_digit(const int k,
                                            const vector<int> &xs) {
    assert(0 <= k && k < sz(xs));
    const auto block_size = k + 1;
    long long result{};

    for (int i = k; i < sz(xs); i += 4 * block_size) {
        for (int j = 0; j <= k; ++j) {
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
    // vector<int> result0;
    // result0.reserve(sz(xs));

    // for (int k = 0; k < sz(xs); ++k) {
    //     result0.push_back(flawed_frequency_transmission_kth_digit(k, xs));
    //     if (k && k % 100000 == 0) {
    //         cerr << "Digit " << k << " computed; per:" <<
    //         tail_period(result0)
    //              << endl;
    //     }
    // }

    {
        vector<int> result;
        result.reserve(sz(xs));

        for (int k = 0; k < 200'000; ++k) {
            result.push_back(flawed_frequency_transmission_kth_digit(k, xs));
        }

        const auto per = tail_period(result);
        assert(per > 0);
        const auto pat = vector(cend(result) - per, cend(result));

        while (sz(result) < sz(xs)) {
            result.insert(cend(result), cbegin(pat), cend(pat));
        }

        result.resize(sz(xs));
        // assert(result == result0);
        return result;
    }

    // cerr << "per:" << tail_period(result0) << endl;
    // return result0;
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
