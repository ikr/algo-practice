#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll proper_intervals_num(const vector<int> &A, const int HI, const int LO) {
    const auto N = sz(A);
    vector<int> his;
    vector<int> los;
    vector<int> sep;

    for (int i = 0; i < sz(A); ++i) {
        if (A[i] == HI) his.push_back(i);
        if (A[i] == LO) los.push_back(i);
        if (A[i] < LO || A[i] > HI) sep.push_back(i);
    }

    ll result{};

    const auto algo = [N, &result](const vector<int> &ss, const vector<int> &xs,
                                   const vector<int> &ys) {
        for (const auto x : xs) {
            const auto sep_it = lower_bound(cbegin(ss), cend(ss), x);
            const auto l1 = sep_it == cbegin(ss) ? -1 : *prev(sep_it);

            const auto ys_it0 = lower_bound(cbegin(ys), cend(ys), x);
            const auto l2 = ys_it0 == cbegin(ys) ? -1 : *prev(ys_it0);

            const auto xs_it0 = lower_bound(cbegin(xs), cend(xs), x);
            const auto l3 = xs_it0 == cbegin(xs) ? -1 : *prev(xs_it0);

            const auto l = max({l1, l2, l3});

            const auto sep_jt = upper_bound(cbegin(ss), cend(ss), x);
            const auto r = sep_jt == cend(ss) ? N : (*sep_jt);

            const auto ys_it = upper_bound(cbegin(ys), cend(ys), x);
            // cerr << "x:" << x << " l:" << l << " r:" << r;
            if (ys_it == cend(ys)) {
                // cerr << " and no y after x!" << endl;
                continue;
            }

            const auto y = *ys_it;
            // cerr << " y:" << y;
            if (y >= r) {
                // cerr << " an y is not before r!" << endl;
                continue;
            }

            const auto d = (x - l) * (r - y);
            // cerr << " d:" << d << endl;
            result += d;
        }
    };

    algo(sep, los, his);
    algo(sep, his, los);

    return HI == LO ? (result / 2 + sz(los)) : result;
}

ll oracle(const vector<int> &a, const int X, const int Y) {
    const int n = sz(a);

    const auto f = [&](const int x, const int y) -> ll {
        if (x > y) {
            return 0;
        }
        ll ans{};
        for (int i = 0; i < n;) {
            if (x <= a[i] && a[i] <= y) {
                int pos = i;
                while (i < n && x <= a[i] && a[i] <= y) {
                    ++i;
                }
                ans += 1LL * (i - pos) * (i - pos + 1) / 2;
            } else {
                ++i;
            }
        }
        return ans;
    };

    return f(Y, X) - f(Y + 1, X) - f(Y, X - 1) + f(Y + 1, X - 1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, X, Y;
    cin >> N >> X >> Y;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    if (oracle(A, X, Y) != proper_intervals_num(A, X, Y)) {
        cerr << "expected:" << oracle(A, X, Y)
             << " actual:" << proper_intervals_num(A, X, Y) << endl;
        return 1;
    }

    cout << proper_intervals_num(A, X, Y) << '\n';
    return 0;
}
