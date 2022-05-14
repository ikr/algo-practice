#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int num_good_up_to_W(const vector<int> &A, const int W) {
    set<int> xs(cbegin(A), cend(A));
    set<int> xxs;
    set<int> xxxs;

    for (int i = 0; i < sz(A) - 1; ++i) {
        for (int j = i + 1; j < sz(A); ++j) {
            xxs.insert(A[i] + A[j]);
        }
    }

    for (int i = 0; i < sz(A) - 2; ++i) {
        for (int j = i + 1; j < sz(A) - 1; ++j) {
            for (int k = j + 1; k < sz(A); ++k) {
                xxxs.insert(A[i] + A[j] + A[k]);
            }
        }
    }

    int result{};
    for (int n = 1; n <= W; ++n) {
        if (xs.count(n) || xxs.count(n) || xxxs.count(n)) ++result;
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, W;
    cin >> N >> W;

    vector<int> A(N);
    for (auto &x : A) cin >> x;
    sort(begin(A), end(A));

    cout << num_good_up_to_W(A, W) << '\n';
    return 0;
}
