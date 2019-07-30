#include <bits/stdc++.h>

using namespace std;

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

    const unsigned int target_size = 1 << I;
    while (intensities.size() > target_size) {
        const auto lo = counts_by_intensity.cbegin()->first;
        const auto hi = counts_by_intensity.crbegin()->first;

        if (counts_by_intensity[lo] < counts_by_intensity[hi]) {
            auto next_lo_it = counts_by_intensity.cbegin();
            ++next_lo_it;
            const auto next_lo = next_lo_it->first;

            counts_by_intensity.erase(lo);
            intensities.erase(lo);

            counts_by_intensity[next_lo] += original_counts_by_intensity[lo];
            ans += original_counts_by_intensity[lo];
        } else {
            auto next_hi_it = counts_by_intensity.crbegin();
            ++next_hi_it;
            const auto next_hi = next_hi_it->first;

            counts_by_intensity.erase(hi);
            intensities.erase(hi);

            counts_by_intensity[next_hi] += original_counts_by_intensity[hi];
            ans += original_counts_by_intensity[hi];
        }
    }

    cout << ans << '\n';
}
