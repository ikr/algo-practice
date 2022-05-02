#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char chof(const int x) { return static_cast<char>(x); }

constexpr int AZ = 26;

vector<string> full_index() {
    vector<string> result{"__"};

    for (int x = 0; x < AZ; ++x) {
        for (int y = 0; y < AZ; ++y) {
            if (x == y) continue;
            result.push_back(string{chof(inof('a') + x), chof(inof('a' + y))});
        }
    }

    sort(begin(result), end(result));
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto idx = full_index();
    const auto lookup = [&idx](const string &x) {
        const auto it = find(cbegin(idx), cend(idx), x);
        return inof(distance(cbegin(idx), it));
    };

    int t;
    cin >> t;
    while (t--) {
        string x;
        cin >> x;
        cout << lookup(x) << '\n';
    }

    return 0;
}
