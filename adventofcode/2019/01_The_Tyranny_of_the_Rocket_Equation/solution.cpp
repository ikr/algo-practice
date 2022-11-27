#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> xs;
    for (string line; getline(cin, line);) {
        xs.push_back(stoi(line));
    }

    const auto result = transform_reduce(cbegin(xs), cend(xs), 0, plus<int>{},
                                         [](const int x) { return x / 3 - 2; });

    cout << result << '\n';
    return 0;
}
