#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s, t;
    cin >> s >> t;

    vector<int> xs;
    int i = -1;
    for (const auto a : s) {
        const auto j = t.find(a, i + 1);
        assert(j != string::npos);
        i = inof(j);
        xs.push_back(i + 1);
    }
    cout << xs << '\n';
    return 0;
}
