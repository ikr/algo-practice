#include <cassert>
#include <iostream>
#include <set>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    set<int> xs;
    for (int i = 1; i <= 2 * n + 1; ++i) xs.insert(i);

    for (;;) {
        assert(!xs.empty());
        cout << *cbegin(xs) << endl;
        xs.erase(cbegin(xs));

        int y;
        cin >> y;
        if (y == 0) break;
        xs.erase(y);
    }

    return 0;
}
