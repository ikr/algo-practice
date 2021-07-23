#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int SZ = 'z' - 'a' + 1;

vi freqs(const string &xs) {
    vi ans(SZ, 0);
    for (const auto x : xs) {
        ++ans[x - 'a'];
    }
    return ans;
}

int num_red(const string &xs) {
    const auto fs = freqs(xs);
    const auto distinct = count(cbegin(fs), cend(fs), 1);
    const auto repeating =
        count_if(cbegin(fs), cend(fs), [](const int x) { return x > 1; });

    return distinct / 2 + repeating;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        cout << num_red(xs) << '\n';
    }

    return 0;
}
