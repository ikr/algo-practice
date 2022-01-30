#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

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

list<int> deconstruct(const string &xs) {
    const auto n = sz(xs);
    list<int> ans;
    ans.push_back(n);

    for (int x = n - 1; x >= 0; --x) {
        const auto i = n - 1 - x;
        if (xs[i] == 'L') {
            ans.push_back(x);
        } else {
            assert(xs[i] == 'R');
            ans.push_front(x);
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    string xs(n, ' ');
    cin >> xs;
    reverse(begin(xs), end(xs));

    cout << deconstruct(xs) << '\n';
    return 0;
}
