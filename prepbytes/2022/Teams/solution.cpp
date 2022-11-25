#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

ll teams_num(const vector<string> &xs) {
    int m{}, a{}, r{}, c{}, h{};

    for (const auto &x : xs) {
        switch (x[0]) {
        case 'M':
            ++m;
            break;

        case 'A':
            ++a;
            break;

        case 'R':
            ++r;
            break;

        case 'C':
            ++c;
            break;

        case 'H':
            ++h;
            break;
        }
    }

    ll result{};
    array<int, 5> cs{m, a, r, c, h};

    for (int i = 0; i < sz(cs) - 2; ++i) {
        for (int j = i + 1; j < sz(cs) - 1; ++j) {
            for (int k = j + 1; k < sz(cs); ++k) {
                result += llof(cs[i]) * llof(cs[j]) * llof(cs[k]);
            }
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<string> xs(N);
    for (auto &x : xs) cin >> x;

    cout << teams_num(xs) << '\n';
    return 0;
}
