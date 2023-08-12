#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

enum class MS { N, U, L };

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    string xs;
    cin >> xs;
    assert(sz(xs) == N);

    unordered_set<int> ind;
    MS ms = MS::N;

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
            ind.insert(i);
            xs[i] = c;
        } else if (t == 2) {
            ms = MS::U;
            ind.clear();
        } else {
            assert(t == 3);
            ms = MS::L;
            ind.clear();
        }
    }

    for (int i = 0; i < sz(xs); ++i) {
        if (!ind.contains(i)) {
            if (ms == MS::U) {
                xs[i] = toupper(xs[i]);
            } else if (ms == MS::L) {
                xs[i] = tolower(xs[i]);
            }
        }
    }

    cout << xs << '\n';
    return 0;
}
