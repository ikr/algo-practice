#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;
    vector<int> A(N);
    for (auto &a : A) cin >> a;

    int M;
    cin >> M;
    vector<int> B(M);
    for (auto &b : B) cin >> b;

    int L;
    cin >> L;
    vector<int> C(L);
    for (auto &c : C) cin >> c;

    unordered_set<int> ss;
    for (const auto a : A) {
        for (const auto b : B) {
            for (const auto c : C) {
                ss.insert(a + b + c);
            }
        }
    }

    int Q;
    cin >> Q;
    for (int q = 1; q <= Q; ++q) {
        int x;
        cin >> x;
        cout << (ss.contains(x) ? "Yes" : "No") << '\n';
    }

    return 0;
}
