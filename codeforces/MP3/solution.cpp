#include <bits/stdc++.h>

using namespace std;

int main() {
    unsigned int n;
    unsigned int I;
    cin >> n >> I;

    map<unsigned int, unsigned int> counts_by_intensity;
    unordered_set<unsigned int> intensities;

    for (unsigned int i = 0; i != n; ++i) {
        unsigned int a;
        cin >> a;

        ++counts_by_intensity[a];
        intensities.insert(a);
    }

    const unsigned int target_size = 1 << I;
    while (intensities.size() > target_size) {
    }
}
