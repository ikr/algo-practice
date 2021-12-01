#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int incs_num(vector<int> xs) {
    adjacent_difference(cbegin(xs), cend(xs), begin(xs));
    return inof(count_if(next(cbegin(xs)), cend(xs),
                         [](const int x) { return x > 0; }));
}

int main() {
    vector<int> xs;

    for (string line; getline(cin, line);) {
        xs.push_back(stoi(line));
    }

    cout << incs_num(move(xs)) << '\n';
    return 0;
}
