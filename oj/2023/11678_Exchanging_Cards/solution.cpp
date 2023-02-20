#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

int count_desirable(const set<int> &src, const set<int> &dst) {
    return inof(count_if(src.cbegin(), src.cend(),
                         [&](const int a) { return !dst.count(a); }));
}

int num_tradeable(const vector<int> &xs, const vector<int> &ys) {
    const set<int> xss(xs.cbegin(), xs.cend());
    const set<int> yss(ys.cbegin(), ys.cend());
    return min(count_desirable(xss, yss), count_desirable(yss, xss));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    for (;;) {
        int A, B;
        cin >> A >> B;
        if (!A && !B) break;

        vector<int> xs(A);
        for (auto &x : xs) cin >> x;

        vector<int> ys(B);
        for (auto &y : ys) cin >> y;

        cout << num_tradeable(xs, ys) << '\n';
    }

    return 0;
}
