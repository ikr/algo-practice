#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int freq_of_one(const vector<string> &xss, const int i) {
    int ans{};
    for (const auto &xs : xss) {
        if (xs[i] == '1') ++ans;
    }
    return ans;
}

vector<string> discriminate(const vector<string> &xss, const int i,
                            const char bit) {
    vector<string> ans;
    copy_if(cbegin(xss), cend(xss), back_inserter(ans),
            [&](const string &xs) { return xs[i] == bit; });
    return ans;
}

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

string rating(const function<char(int, int)> which_bit, vector<string> xss,
              const int i) {
    assert(!xss.empty());
    if (sz(xss) == 1 || i >= sz(xss[0])) return xss[0];

    const auto foo = freq_of_one(xss, i);
    const auto maj = div_ceil(sz(xss), 2);
    xss = discriminate(xss, i, which_bit(foo, maj));
    return rating(which_bit, xss, i + 1);
}

string o2_gen_rating(vector<string> xss) {
    return rating(
        [](const int foo, const int maj) { return foo >= maj ? '1' : '0'; },
        xss, 0);
}

string co2_scrubber_rating(vector<string> xss) {
    return rating(
        [](const int foo, const int maj) { return foo >= maj ? '0' : '1'; },
        xss, 0);
}

ll as_ll(const string &bits) { return llof(bitset<30>(bits).to_ulong()); }

ll life_support_rating(const vector<string> &xss) {
    return as_ll(o2_gen_rating(xss)) * as_ll(co2_scrubber_rating(xss));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    vector<string> xss;

    for (string line; getline(cin, line);) {
        xss.push_back(line);
    }

    cout << life_support_rating(xss) << '\n';
    return 0;
}
