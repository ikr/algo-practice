#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<vector<int>> xss(1);
    for (string line; getline(cin, line);) {
        if (line == "") {
            xss.push_back({});
            continue;
        }

        xss.back().push_back(stoi(line));
    }

    vector<int> xs(xss.size());
    transform(cbegin(xss), cend(xss), begin(xs), [](const auto &ys) {
        return accumulate(cbegin(ys), cend(ys), 0);
    });

    partial_sort(begin(xs), begin(xs) + 3, end(xs), greater<int>{});
    cout << accumulate(cbegin(xs), cbegin(xs) + 3, 0) << '\n';
    return 0;
}
