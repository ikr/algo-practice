#include <bits/stdc++.h>
using namespace std;

constexpr int req_unit(const int x) { return x / 3 - 2; }

int fuel_needed(int x) {
    int result{};

    while (req_unit(x) >= 0) {
        result += req_unit(x);
        x = req_unit(x);
    }

    return result;
}

int main() {
    vector<int> xs;
    for (string line; getline(cin, line);) {
        xs.push_back(stoi(line));
    }

    const auto result =
        transform_reduce(cbegin(xs), cend(xs), 0, plus<int>{}, fuel_needed);

    cout << result << '\n';
    return 0;
}
