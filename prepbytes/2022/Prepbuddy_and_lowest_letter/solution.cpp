#include <iostream>
#include <iterator>
#include <set>
#include <string>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char chof(const int x) { return static_cast<char>(x); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        set<char> missing;
        for (int i = 0; i < 26; ++i) {
            missing.insert(chof(inof('a') + i));
        }

        for (const auto x : xs) {
            missing.erase(x);
        }

        cout << (missing.empty() ? string{"NA"} : string{*cbegin(missing)})
             << '\n';
    }

    return 0;
}
