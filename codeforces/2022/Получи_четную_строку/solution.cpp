#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;
constexpr int az_to_i(const char c) {
    return static_cast<int>(c) - static_cast<int>('a');
}

int min_ops(const string &xs) {
    vector<vector<int>> idx(AZ);
    set<int> singles;

    string ys;
    for (int i = 0; i < sz(xs);) {
        if (i < sz(xs) - 1) {
            if (xs[i] == xs[i + 1]) {
                i += 2;
            } else {
                idx[az_to_i(xs[i])].push_back(i);
                singles.insert(i);
                ++i;
            }
        } else {
            idx[az_to_i(xs[i])].push_back(i);
            singles.insert(i);
            ++i;
        }
    }

    int result{};

    for (const auto &ii : idx) {
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        cout << min_ops(xs) << '\n';
    }

    return 0;
}
