#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;

constexpr int op(const int a, const int b) { return a ^ b; }
constexpr int e() { return 0; }
using tri = tuple<int, int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int solution(vector<int> xs, const vector<tri> &qs) {
    atcoder::segtree<int, op, e> seg(xs);
    map<int, set<int>> idx;
    for (int i = 0; i < sz(xs); ++i) idx[xs[i]].insert(i);

    const auto change_value = [&](const int i, const int x_) -> void {
        const auto x = xs[i];
        xs[i] = x_;
        seg.set(i, x_);
        idx[x].erase(i);
        idx[x_].insert(i);
    };

    int result{};
    for (const auto &[a, b, c] : qs) {
        if (a == 1) {
            change_value(b - 1, c);
        } else {
            assert(a == 2);
            const auto L = b - 1;
            const auto R = c - 1;

            if ((R - L + 1) % 2 == 0) continue;

            if (L == R) {
                ++result;
                continue;
            }

            const auto m = (L + R) / 2;

            {
                const auto XL = seg.prod(L, m + 1);
                const auto XR = seg.prod(m + 1, R + 1);
                const auto x = XL ^ XR;

                if (idx.contains(x)) {
                    const auto it = idx.at(x).lower_bound(L);
                    if (it != cend(idx.at(x)) && *it <= m) {
                        ++result;
                        continue;
                    }
                }
            }

            {
                const auto XL = seg.prod(L, m);
                const auto XR = seg.prod(m, R + 1);
                const auto x = XL ^ XR;

                if (idx.contains(x)) {
                    const auto it = idx.at(x).lower_bound(m);
                    if (it != cend(idx.at(x)) && *it <= R) ++result;
                }
            }
        }
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<int> xs(N);
        for (auto &x : xs) cin >> x;

        int Q;
        cin >> Q;
        vector<tri> qs(Q);

        for (auto &[a, b, c] : qs) {
            cin >> a >> b >> c;
        }

        cout << "Case #" << i << ": " << solution(move(xs), qs) << '\n';
    }

    return 0;
}
