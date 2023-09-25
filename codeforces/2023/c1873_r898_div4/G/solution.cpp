#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<char, int>> run_length_encode(const string &xs) {
    vector<pair<char, int>> ans{{xs[0], 1}};
    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] == ans.back().first) {
            ++(ans.back().second);
        } else {
            ans.emplace_back(xs[i], 1);
        }
    }
    return ans;
}

int max_coins(const string &xs) {
    auto rle = run_length_encode(xs);
    int result{};

    const auto sweep_left_edge_Bs = [&]() {
        for (int i = 0; i < sz(rle) - 1; ++i) {
            if (rle[i].first != 'B') continue;
            if (i && rle[i - 1].first == 'A') continue;
            if (rle[i + 1].first != 'A') continue;

            result += rle[i + 1].second;
            rle[i].first = 'C';
            rle[i + 1].first = 'B';
        }
    };

    const auto sweep_mid_Bs = [&]() {
        for (int i = 1; i < sz(rle) - 1;) {
            if (rle[i].first != 'B' || rle[i - 1].first != 'A' ||
                rle[i + 1].first != 'A') {
                ++i;
            } else {
                if (rle[i].second > 1) {
                    result += rle[i - 1].second + rle[i + 1].second;
                    rle[i - 1].first = 'C';
                    rle[i + 1].first = 'C';
                } else {
                    if (rle[i - 1].second >= rle[i + 1].second) {
                        result += rle[i - 1].second;
                        rle[i - 1].first = 'B';
                        rle[i].first = 'C';
                    } else {
                        result += rle[i + 1].second;
                        rle[i + 1].first = 'B';
                        rle[i].first = 'C';
                    }
                }
                i += 2;
            }
        }
    };

    sweep_left_edge_Bs();
    ranges::reverse(rle);
    sweep_left_edge_Bs();

    sweep_mid_Bs();
    sweep_left_edge_Bs();
    ranges::reverse(rle);
    sweep_left_edge_Bs();

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
        cout << max_coins(xs) << '\n';
    }
    return 0;
}
