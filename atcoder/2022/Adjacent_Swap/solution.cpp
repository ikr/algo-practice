#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> final_state(const int N, const vector<int> &xs) {
    vector<int> ans(N);
    iota(begin(ans), end(ans), 1);

    vector<int> idx(N + 1);
    iota(begin(idx), end(idx), -1);
    assert(idx[1] == 0);
    assert(idx[N] == N - 1);

    for (const auto x : xs) {
        const auto i = idx[x];
        const auto i_ = (i == N - 1) ? (i - 1) : i + 1;
        const auto x_ = ans[i_];

        ans[i] = x_;
        ans[i_] = x;

        idx[x_] = i;
        idx[x] = i_;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, Q;
    cin >> N >> Q;

    vector<int> xs(Q);
    for (auto &x : xs) cin >> x;

    const auto ys = final_state(N, xs);
    for (auto i = ys.cbegin(); i != ys.cend(); ++i) {
        if (i != ys.cbegin()) cout << ' ';
        cout << *i;
    }
    cout << endl;

    return 0;
}
