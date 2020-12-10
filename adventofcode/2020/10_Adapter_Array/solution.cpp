#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> xs{0};
    for (string line; getline(cin, line);) {
        xs.push_back(stoi(line));
    }
    sort(begin(xs), end(xs));
    xs.push_back(xs.back() + 3);

    vector<int> ds(xs.size(), 0);
    adjacent_difference(cbegin(xs), cend(xs), begin(ds));

    const int d1s = count(cbegin(ds), cend(ds), 1);
    const int d3s = count(cbegin(ds), cend(ds), 3);

    cout << (d1s * d3s) << '\n';
    return 0;
}
