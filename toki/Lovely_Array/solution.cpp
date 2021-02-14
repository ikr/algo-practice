#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> bits_on(const bitset<15> &bs) {
    vector<int> ans;
    for (int i = 0; i < 15; ++i) {
        if (bs.test(i)) ans.push_back(i);
    }
    return ans;
}

vector<int> construct_xs(const int k) {
    const auto k_bs = bitset<15>(k);
    const int h = 2 * k_bs.count();

    vector<bitset<30>> table(h, bitset<30>((1 << 30) - 1));
    const auto bis = bits_on(k_bs);
    for (auto i = 0U; i < bis.size(); ++i) {
        const int bi = bis[i];
        for (int j = 2 * i + 1; j < h; ++j) table[j][bi] = false;
    }

    for (auto d = 0U; d < bis.size(); ++d) {
        const int bi = 29 - d;
        for (int j = (d + 1) * 2; j < h; ++j) table[j][bi] = false;
    }

    vector<int> ans(h, 0);
    transform(cbegin(table), cend(table), begin(ans),
              [](const auto &bs) -> int { return bs.to_ulong(); });
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int k;
    cin >> k;

    const auto xs = construct_xs(k);
    cout << xs.size() << '\n';
    cout << xs << '\n';

    return 0;
}
