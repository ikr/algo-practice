#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    map<string, int> idx{};
    int next_id{1};

    int t;
    cin >> t;
    while (t--) {
        string name;
        cin >> name;

        if (idx.contains(name)) {
            cout << idx.at(name) << '\n';
        } else {
            cout << next_id << '\n';
            idx.emplace(name, next_id);
            ++next_id;
        }
    }

    return 0;
}
