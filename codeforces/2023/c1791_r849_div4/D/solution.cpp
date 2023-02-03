#include <bits/stdc++.h>
using namespace std;

static constexpr int AZ = 26;

using Freqs = array<int, AZ>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T, size_t N>
constexpr array<T, N> operator-(array<T, N> a, const array<T, N> &b) {
    transform(cbegin(a), cend(a), cbegin(b), begin(a), minus<int>{});
    return a;
}

Freqs zeros() {
    Freqs ans;
    ans.fill(0);
    return ans;
}

int f_of(const Freqs &fs) {
    return inof(
        count_if(cbegin(fs), cend(fs), [](const int f) { return f > 0; }));
}

int max_sum_of_fs(const string &xs) {
    vector<Freqs> ss(sz(xs), zeros());
    ss[0][inof(xs[0]) - inof('a')] = 1;

    for (int i = 1; i < sz(xs); ++i) {
        const auto x = inof(xs[i]) - inof('a');
        ss[i] = ss[i - 1];
        ++ss[i][x];
    }

    int ans{};
    for (int i = 0; i < sz(xs) - 1; ++i) {
        const auto fa = f_of(ss[i]);
        const auto fb = f_of(ss.back() - ss[i]);
        ans = max(ans, fa + fb);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;

        assert(sz(xs) == n);
        cout << max_sum_of_fs(xs) << '\n';
    }

    return 0;
}
