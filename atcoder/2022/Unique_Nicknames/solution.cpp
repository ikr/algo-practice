#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool nicks_possible(const vector<pair<string, string>> &names) {
    map<string, int> fs;
    for (const auto &[fn, gn] : names) {
        if (fn == gn) {
            ++fs[fn];
        } else {
            ++fs[fn];
            ++fs[gn];
        }
    }

    for (const auto &[fn, gn] : names) {
        if (fs[fn] > 1 && fs[gn] > 1) return false;
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<pair<string, string>> names(N);
    for (auto &[fn, gn] : names) cin >> fn >> gn;

    cout << (nicks_possible(names) ? "Yes" : "No") << '\n';
    return 0;
}
