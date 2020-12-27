#include <bits/stdc++.h>
#include <numeric>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const deque<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

int solve(deque<int> xs, deque<int> ys) {
    while (!xs.empty() && !ys.empty()) {
        const int x = xs.front();
        xs.pop_front();

        const int y = ys.front();
        ys.pop_front();

        if (x > y) {
            xs.push_back(x);
            xs.push_back(y);
        } else {
            ys.push_back(y);
            ys.push_back(x);
        }
    }

    const auto &zs = xs.empty() ? ys : xs;
    const int n = zs.size();
    vector fs(n, 0);
    iota(begin(fs), end(fs), 1);
    reverse(begin(fs), end(fs));


    return inner_product(cbegin(zs), cend(zs), cbegin(fs), 0);
}

int main() {
    deque<int> xs;
    deque<int> ys;

    bool one = true;
    for (string line; getline(cin, line);) {
        if (line == "Player 1:") continue;
        if (line == "") {
            continue;
        }
        if (line == "Player 2:") {
            one = false;
            continue;
        }

        const int n = stoi(line);
        if (one) {
            xs.push_back(n);
        } else {
            ys.push_back(n);
        }
    }

    cout << solve(xs, ys) << '\n';
    return 0;
}
