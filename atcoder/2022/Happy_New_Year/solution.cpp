#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

void remove_leading_zeros(string &ds) {
    for (auto it = ds.begin(); it != ds.end();) {
        if (*it != '0') break;
        it = ds.erase(it);
    }
}

string kth_smallest(const ull k) {
    const bitset<64> bits(k);
    string ans(64, '0');
    for (int i = 0; i < 64; ++i) {
        if (bits[i]) {
            ans[i] = '2';
        }
    }

    reverse(begin(ans), end(ans));
    remove_leading_zeros(ans);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ull k;
    cin >> k;

    cout << kth_smallest(k) << '\n';
    return 0;
}
