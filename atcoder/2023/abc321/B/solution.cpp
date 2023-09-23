#include <bits/stdc++.h>
using namespace std;

static constexpr int INF = INT_MAX;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_last_score(const vector<int> &A, const int X) {
    int result = INF;

    for (int y = 0; y <= 100; ++y) {
        auto B = A;
        B.push_back(y);
        ranges::sort(B);

        const auto cur = accumulate(cbegin(B) + 1, cend(B) - 1, 0);
        if (cur >= X) {
            result = y;
            break;
        }
    }

    return result == INF ? -1 : result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, X;
    cin >> N >> X;

    vector<int> A(N - 1);
    for (auto &a : A) cin >> a;

    cout << min_last_score(A, X) << '\n';
    return 0;
}
