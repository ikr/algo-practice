#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> positions_of_ones(const int N, const vector<int> &A) { return A; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<int> A(M);
    for (auto &a : A) cin >> a;

    for (const auto i : positions_of_ones(N, A)) {
        cout << i << '\n';
    }
    return 0;
}
