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

vector<int> combine_slices(const vector<vector<int>> &xss) {
    assert(!xss.empty());
    const auto k = sz(xss[0]);
    vector<int> result(k, 0);

    for (int j = 0; j < k; ++j) {
        for (int i = 0; i < sz(xss); ++i) {
            if (xss[i][j] == 2) continue;
            result[j] = xss[i][j];
            break;
        }
    }

    return result;
}

vector<string> raster_of_a_slice(const int W, const vector<int> &xs) {
    const auto H = sz(xs) / W;
    vector<string> result(H, string(W, ' '));

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (xs[ro * W + co]) result[ro][co] = '*';
        }
    }

    return result;
}

int main() {
    string line;
    cin >> line;

    vector<int> xs(sz(line));
    transform(cbegin(line), cend(line), begin(xs),
              [](const char c) { return inof(c) - inof('0'); });

    const int H = 6;
    const int W = 25;

    const auto combined = combine_slices(cut_evenly(xs, H * W));
    for (const auto &row : raster_of_a_slice(W, combined)) {
        cout << row << '\n';
    }
    return 0;
}
