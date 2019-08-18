#include <bits/stdc++.h>

using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    return os;
}

int main() {
    int n;
    cin >> n;

    if (n % 2 == 0) {
        cout << "NO\n";
        return 0;
    }

    vector<int> xs(2 * n);

    for (int i = 1; i <= 2 * n - 1; i += 2) {
        xs[i - 1] = i;
    }

    for (int i = 1; i <= 2 * n - 1; i += 2) {
        xs[i - 1] = i;
    }

    for (int i = 2; i <= 2 * n; i += 2) {
        xs[(n + i - 2) % (2 * n)] = i;
    }

    cout << "YES\n";
    cout << xs << '\n';
    return 0;
}
