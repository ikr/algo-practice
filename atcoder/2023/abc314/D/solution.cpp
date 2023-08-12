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

    string xs;
    cin >> xs;
    assert(sz(xs) == N);

    unordered_set<int> up;
    unordered_set<int> lo;
    for (int i = 0; i < sz(xs); ++i) {
        if (isupper(xs[i])) {
            up.insert(i);
        } else if (islower(xs[i])) {
            lo.insert(i);
        }
    }

    int Q;
    cin >> Q;
    for (int q = 0; q < Q; ++q) {
        int t, i;
        cin >> t >> i;
        --i;

        char c;
        cin >> c;

        if (t == 1) {
            xs[i] = c;
            if (isupper(c)) {
                up.insert(i);
                lo.erase(i);
            } else {
                assert(islower(c));
                lo.insert(i);
                up.erase(i);
            }
        } else if (t == 2) {
            if (lo.empty()) {
                swap(up, lo);
            } else {
                lo.insert(cbegin(up), cend(up));
                up.clear();
            }
        } else {
            assert(t == 3);

            if (up.empty()) {
                swap(lo, up);
            } else {
                up.insert(cbegin(lo), cend(lo));
                lo.clear();
            }
        }
    }

    for (int i = 0; i < sz(xs); ++i) {
        if (up.contains(i)) {
            xs[i] = toupper(xs[i]);
        } else if (lo.contains(i)) {
            xs[i] = tolower(xs[i]);
        }
    }

    cout << xs << '\n';
    return 0;
}
