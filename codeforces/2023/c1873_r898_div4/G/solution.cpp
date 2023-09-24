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

    for (int i = 0; i < sz(rle); ++i) {
        const auto [x, f] = rle[i];
        if (x != 'A') continue;

        if (i && rle[i - 1].first == 'B' && rle[i - 1].second) {
            result += f;
            continue;
        }

        if (i < sz(rle) - 1 && rle[i + 1].first == 'B' && rle[i + 1].second) {
            --rle[i + 1].second;
            result += f;
        }
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

        cout << max_coins(xs) << '\n';
    }

    return 0;
}
