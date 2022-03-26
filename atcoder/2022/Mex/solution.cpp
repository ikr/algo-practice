#include <iostream>
#include <vector>
#include <set>
using namespace std;

template <typename T> constexpr int inof(const T x) { return static_cast<int>(x); }

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    set<int> ss(cbegin(xs), cend(xs));
    for (int i = 0; i <= 2001; ++i) {
        if (!ss.count(i)) {
            cout << i << '\n';
            break;
        }
    }

    return 0;
}
