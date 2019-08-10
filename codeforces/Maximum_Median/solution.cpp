#include <bits/stdc++.h>

using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    return os;
}

int main() {
    int n;
    int k;
    cin >> n >> k;

    vector<int> xs(n);
    for (auto &x : xs) {
        cin >> x;
    }

    sort(begin(xs), end(xs));
    copy(cbegin(xs) + xs.size() / 2, cend(xs), begin(xs));
    xs.resize(xs.size() / 2 + 1);

    cout << xs << '\n';
}
