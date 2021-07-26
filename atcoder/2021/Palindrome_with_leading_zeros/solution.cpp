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

vector<int> digits_reversed(int x) {
    vector<int> ans;
    while (x) {
        ans.push_back(x % 10);
        x /= 10;
    }
    return ans;
}

bool is_possible(const int x) {
    auto ds = digits_reversed(x);
    const auto nz_it =
        find_if(cbegin(ds), cend(ds), [](const int y) { return y != 0; });

    const vi mid(nz_it, cend(ds));
    vi mid_ = mid;
    reverse(begin(mid_), end(mid_));
    return mid == mid_;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    cout << (is_possible(t) ? "Yes\n" : "No\n");

    return 0;
}
