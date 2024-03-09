#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const list<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    list<int> A;
    map<int, list<int>::const_iterator> idx;
    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        A.push_back(a);
        idx.emplace(a, prev(end(A)));
    }

    int Q;
    cin >> Q;
    for (int q = 1; q <= Q; ++q) {
        int cmd;
        cin >> cmd;

        if (cmd == 1) {
            int x, y;
            cin >> x >> y;

            const auto it = next(idx.at(x));
            const auto jt = A.insert(it, y);
            idx.emplace(y, jt);
        } else {
            assert(cmd == 2);
            int x;
            cin >> x;

            A.erase(idx.at(x));
            idx.erase(x);
        }
    }

    cout << A << '\n';
    return 0;
}
