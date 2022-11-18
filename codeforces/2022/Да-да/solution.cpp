#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const set<char> ALL{'Y', 'e', 's'};

bool is_ok(const string &xs) {
    if (sz(xs) == 2) {
        return xs == "Ye" || xs == "es" || xs == "sY";
    }

    if (!ALL.count(xs[0])) return false;
    if (!ALL.count(xs.back())) return false;

    for (int i = 1; i < sz(xs) - 1; ++i) {
        switch (xs[i]) {
        case 'Y':
            if (!(xs[i - 1] == 's' && xs[i + 1] == 'e')) return false;
            break;

        case 'e':
            if (!(xs[i - 1] == 'Y' && xs[i + 1] == 's')) return false;
            break;

        case 's':
            if (!(xs[i - 1] == 'e' && xs[i + 1] == 'Y')) return false;
            break;

        default:
            return false;
        }
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        cout << (is_ok(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
