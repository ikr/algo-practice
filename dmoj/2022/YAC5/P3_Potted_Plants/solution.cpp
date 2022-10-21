#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> prep_seq(const int K) {
    vector<int> xs(K);
    iota(begin(xs), end(xs), 1);

    while (xs.back() > 2) {
        xs.push_back(xs.back() - 2);
    }

    auto result = xs;
    auto tail = xs;
    reverse(begin(tail), end(tail));
    result.insert(cend(result), cbegin(tail), cend(tail));
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int K;
    cin >> K;

    cout << prep_seq(K) << '\n';
    return 0;
}
