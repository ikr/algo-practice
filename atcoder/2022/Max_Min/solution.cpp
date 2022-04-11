#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int proper_intervals_num(const vector<int> &A, const int HI, const int LO) {
    const auto N = sz(A);
    vector<int> his;
    vector<int> los;
    vector<int> sep;

    for (int i = 0; i < sz(A); ++i) {
        if (A[i] == HI) his.push_back(i);
        if (A[i] == LO) los.push_back(i);
        if (A[i] < LO || A[i] > HI) sep.push_back(i);
    }

    int result{};

    const auto algo = [N, &result](const vector<int> &ss, const vector<int> &xs,
                                   const vector<int> &ys) {
        for (const auto x : xs) {
            const auto sep_it = upper_bound(cbegin(ss), cend(ss), x);
            const auto r = sep_it == cend(ss) ? N : (*sep_it);

            const auto ys_it = lower_bound(cbegin(ys), cend(ys), r);
            if (ys.empty() || ys_it == cbegin(ys)) continue;
            const auto y = *prev(ys_it);
            if (y < x) continue;

            const auto y0_it = lower_bound(cbegin(ys), cend(ys), x);
            const auto y0 = inof(distance(cbegin(ys), y0_it));

            if (y0 > y) continue;
            result += y - y0 + 1;
        }
    };

    algo(sep, los, his);
    algo(sep, his, los);

    return HI == LO ? result / 2 : result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, X, Y;
    cin >> N >> X >> Y;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    cout << proper_intervals_num(A, X, Y) << '\n';
    return 0;
}
