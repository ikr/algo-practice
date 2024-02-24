#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

constexpr char chof(const int x) { return static_cast<char>(x); }

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

    vector<char> idx(26, 'a');
    for (int i = 1; i < sz(idx); ++i) {
        idx[i] = chof('a' + i);
    }

    // cerr << idx << endl;

    int Q;
    cin >> Q;
    for (int i = 1; i <= Q; ++i) {
        char a, b;
        cin >> a >> b;

        for (auto &x : idx) {
            if (x == a) x = b;
        }
    }

    for (auto &x : xs) {
        x = idx[inof(x - 'a')];
    }

    cout << xs << '\n';
    return 0;
}
