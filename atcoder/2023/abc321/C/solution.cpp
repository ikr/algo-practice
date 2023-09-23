#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll kth_321_num(const int k) {
    vector<ll> xs;

    const auto recur = [&](const auto self, const string &cur) -> void {
        xs.push_back(stoll(cur));
        const int hi = cur.back() - '0';
        for (int i = hi - 1; i >= 0; --i) {
            auto cur_ = cur + to_string(i);
            self(self, cur_);
        }
    };

    for (int i = 9; i >= 1; --i) {
        recur(recur, to_string(i));
    }

    ranges::sort(xs);
    return xs[k - 1];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int k;
    cin >> k;
    cout << kth_321_num(k) << '\n';
    return 0;
}
