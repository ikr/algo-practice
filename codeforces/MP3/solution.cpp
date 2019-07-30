#include <bits/stdc++.h>

using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const unordered_set<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    return os;
}

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '{' << i->first << ' ' << i->second << '}';
    }

    return os;
}

int main() {
    unsigned int n;
    unsigned int I;
    cin >> n >> I;

    unordered_map<unsigned int, unsigned int> original_counts_by_intensity;
    map<unsigned int, unsigned int> counts_by_intensity;
    unordered_set<unsigned int> intensities;

    for (unsigned int i = 0; i != n; ++i) {
        unsigned int a;
        cin >> a;

        ++original_counts_by_intensity[a];
        ++counts_by_intensity[a];
        intensities.insert(a);
    }

    unsigned int ans{0};
    cout << counts_by_intensity << '\n';
    cout << intensities << '\n';

    const unsigned int target_size = 1 << I;
    while (intensities.size() > target_size) {
        const auto lo = counts_by_intensity.cbegin()->first;
        const auto hi = counts_by_intensity.crbegin()->first;

        if (counts_by_intensity[lo] < counts_by_intensity[hi]) {
            auto next_lo_it = counts_by_intensity.cbegin();
            ++next_lo_it;
            const auto next_lo = next_lo_it->first;
            const auto capped_count = counts_by_intensity[lo];

            counts_by_intensity.erase(lo);
            intensities.erase(lo);

            counts_by_intensity[next_lo] += capped_count;
            ans += original_counts_by_intensity[lo];
        } else {
            auto next_hi_it = counts_by_intensity.crbegin();
            ++next_hi_it;
            const auto next_hi = next_hi_it->first;
            const auto capped_count = counts_by_intensity[hi];

            counts_by_intensity.erase(hi);
            intensities.erase(hi);

            counts_by_intensity[next_hi] += capped_count;
            ans += original_counts_by_intensity[hi];
        }

        cout << counts_by_intensity << '\n';
        cout << intensities << '\n';
    }

    cout << ans << '\n';
}
