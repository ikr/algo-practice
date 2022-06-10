#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(vector<int> A, vector<int> B) {
    vector<int> ds(sz(A));
    transform(cbegin(A), cend(A), cbegin(B), begin(ds),
              [](const int a, const int b) -> int { return a - b; });

    if (any_of(cbegin(ds), cend(ds), [](const int d) { return d < 0; })) {
        return false;
    }

    const auto dhi = *max_element(cbegin(ds), cend(ds));

    for (int i = 0; i < sz(ds); ++i) {
        if (B[i] == 0) {
            if (A[i] - dhi <= 0) {
                continue;
            } else {
                return false;
            }
        } else {
            if (A[i] - dhi != B[i]) return false;
        }
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> A(n);
        for (auto &a : A) cin >> a;

        vector<int> B(n);
        for (auto &b : B) cin >> b;

        assert(sz(A) == sz(B));
        cout << (is_possible(move(A), move(B)) ? "YES" : "NO") << '\n';
    }

    return 0;
}
