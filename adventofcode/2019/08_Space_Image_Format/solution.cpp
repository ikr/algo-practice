#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> cut_evenly(const vector<int> &xs, const int k) {
    const int n = sz(xs);
    vector<vector<int>> result(n / k, vector(k, 0));

    for (int i = 0; i < n / k; ++i) {
        copy(cbegin(xs) + i * k, cbegin(xs) + (i + 1) * k, begin(result[i]));
    }

    return result;
}

int freq_of(const int x, const vector<int> &xs) {
    return inof(count(cbegin(xs), cend(xs), x));
}

int main() {
    string line;
    cin >> line;

    vector<int> xs(sz(line));
    transform(cbegin(line), cend(line), begin(xs),
              [](const char c) { return inof(c) - inof('0'); });

    const int H = 6;
    const int W = 25;

    const auto slices = cut_evenly(xs, H * W);
    const auto fewest_zeros_slice = *min_element(
        cbegin(slices), cend(slices), [](const auto &a, const auto &b) {
            return freq_of(0, a) < freq_of(0, b);
        });

    cout << (freq_of(1, fewest_zeros_slice) * freq_of(2, fewest_zeros_slice))
         << '\n';
    return 0;
}
