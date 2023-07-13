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

vector<int> ys_compressed(const vector<Tri> &boxes) {
    set<int> y_values_set;
    for (const auto &box : boxes) y_values_set.insert(box[1]);

    vector<int> y_values(cbegin(y_values_set), cend(y_values_set));
    unordered_map<int, int> idx;
    for (int i = 0; i < sz(y_values); ++i) idx[y_values[i]] = i;

    vector<int> result(sz(boxes));
    for (int i = 0; i < sz(boxes); ++i) result[i] = idx.at(boxes[i][1]);
    return result;
}

bool can_nest(const vector<Tri> &boxes) {
    const auto yc = ys_compressed(boxes);
    atcoder::segtree<int, op, e> zs(sz(boxes));
    vector<Duo> stash;

    for (int i = 0; i < sz(boxes); ++i) {
        if (i && boxes[i][0] != boxes[i - 1][0]) {
            for (const auto &[y, z] : stash) zs.set(y, min(zs.get(y), z));
            stash.clear();
        }

        if (zs.prod(0, yc[i]) < boxes[i][2]) return true;
        stash.emplace_back(yc[i], boxes[i][2]);
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

    sort(begin(boxes), end(boxes));
    cout << (can_nest(boxes) ? "Yes" : "No") << '\n';
    return 0;
}
