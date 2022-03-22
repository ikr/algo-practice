#include <iostream>
#include <map>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<int, int> gather_freqs(const int d, const vector<int> &xs) {
    map<int, int> result;
    for (const auto x : xs) {
        ++result[x - d];
        ++result[x];
        ++result[x + d];
    }
    return result;
}

int most_popular(const map<int, int> &fs) {
    int result = cbegin(fs)->first;
    int hi_f = cbegin(fs)->second;

    for (const auto [k, v] : fs) {
        if (v > hi_f) {
            result = k;
            hi_f = v;
        }
    }

    return result;
}

int max_freq_of_y(const int d, const vector<int> &xs) {
    const auto y = most_popular(gather_freqs(d, xs));
    int result{};

    for (const auto x : xs) {
        if (x == y || abs(x - y) == d) ++result;
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        int d;
        cin >> d;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_freq_of_y(d, xs) << '\n';
    }

    return 0;
}
