#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;

using Duo = pair<int, int>;
using Tri = array<int, 3>;

using namespace atcoder;

constexpr int op(const int a, const int b) { return min(a, b); }
constexpr int e() { return INT_MAX; }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool can_nest(const vector<Tri> &boxes) {
    vector<Duo> ys_with_index(sz(boxes));
    for (int i = 0; i < sz(boxes); ++i) {
        ys_with_index[i] = {boxes[i][1], i};
    }
    sort(begin(ys_with_index), end(ys_with_index));

    vector<int> ys_compressed(sz(ys_with_index));
    for (int i = 0; i < sz(ys_with_index); ++i) {
        ys_compressed[ys_with_index[i].second] = i;
    }

    atcoder::segtree<int, op, e> zs(sz(boxes));
    for (int i = 0; i < sz(boxes); ++i) {
        if (zs.prod(0, ys_compressed[i]) < boxes[i][2]) return true;
        zs.set(ys_compressed[i], boxes[i][2]);
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<Tri> boxes(N);

    for (auto &box : boxes) {
        for (auto &x : box) cin >> x;
        sort(begin(box), end(box));
    }

    cout << (can_nest(boxes) ? "Yes" : "No") << '\n';
    return 0;
}
