#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<char, int>> run_length_encode(const string &xs) {
    vector<pair<char, int>> ans{{xs[0], 1}};
    for (int i = 1; i < sz(xs); ++i) {
        if (ans.back().first == xs[i]) {
            ++(ans.back().second);
        } else {
            ans.emplace_back(xs[i], 1);
        }
    }
    return ans;
}

vector<int> special_rle(const string &xs) {
    auto rle = run_length_encode(xs);
    if (sz(rle) > 2 && rle[0].first == rle.back().first) {
        const auto d = rle.back().second;
        rle.pop_back();
        rle[0].second += d;
    }

    vector<int> result(sz(rle));
    transform(cbegin(rle), cend(rle), begin(result),
              [](const auto &ab) { return ab.second; });
    return result;
}

int winner_index(const string &xs) {
    const auto rle = special_rle(xs);
    int compression_parity{};

    for (const auto l : rle) {
        compression_parity += l - 1;
        compression_parity %= 2;
    }

    const auto k0 = sz(rle);
    if (k0 < 3) return !compression_parity;

    map<pair<int, int>, int> memo;
    const auto recur = [&](const auto self, const int a, const int k) {
        if (memo.contains(pair{a, k})) return memo.at(pair{a, k});

        return memo[pair{a, k}] = [&]() -> int {
            if (k == 2) return a;
            return self(self, !a, k - 1);
        }();
    };

    return recur(recur, compression_parity, k0);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << (winner_index(xs) ? "Bob" : "Alice") << '\n';
    }

    return 0;
}
