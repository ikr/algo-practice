#include <cassert>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll M = 1e9 + 7;

static const string VS{'a', 'e', 'i', 'o', 'u'};

bool is_vowel(const char x) { return VS.find(x) != VS.npos; }

int num_opts(const char x) {
    multiset<int> ds;
    for (const auto v : VS) {
        ds.insert(abs(inof(v) - inof(x)));
    }

    const auto d1 = *cbegin(ds);
    const auto d2 = *next(cbegin(ds));
    return d1 == d2 ? 2 : 1;
}

int num_beautiful(const string &xs) {
    ll result = 1;

    for (const auto x : xs) {
        if (is_vowel(x)) continue;
        result *= num_opts(x);
        result %= M;
    }

    return inof(result);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        string S;
        cin >> S;
        assert(sz(S) == N);

        cout << num_beautiful(S) << '\n';
    }

    return 0;
}
