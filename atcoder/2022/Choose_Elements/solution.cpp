#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool xs_exist(const int K, const vector<int> &A, const vector<int> &B) {
    assert(sz(A) == sz(B));
    vector<pair<bool, bool>> dp(sz(A), {false, false});
    dp[0] = pair{true, true};

    for (int i = 1; i < sz(dp); ++i) {
        dp[i].first = [&]() -> bool {
            if (dp[i - 1].first && abs(A[i - 1] - A[i]) <= K) return true;
            if (dp[i - 1].second && abs(B[i - 1] - A[i]) <= K) return true;
            return false;
        }();

        dp[i].second = [&]() -> bool {
            if (dp[i - 1].first && abs(A[i - 1] - B[i]) <= K) return true;
            if (dp[i - 1].second && abs(B[i - 1] - B[i]) <= K) return true;
            return false;
        }();
    }

    return dp.back().first || dp.back().second;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    vector<int> A(n);
    for (auto &a : A) cin >> a;

    vector<int> B(n);
    for (auto &b : B) cin >> b;

    cout << (xs_exist(k, A, B) ? "Yes" : "No") << '\n';
    return 0;
}
