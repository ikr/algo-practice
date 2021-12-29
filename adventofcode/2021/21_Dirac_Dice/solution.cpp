#include <bits/stdc++.h>
using namespace std;

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

int roll_value(const int n) {
    const auto cycle = [](const int x) -> int { return ((x - 1) % 100) + 1; };
    const int base = 3 * (n - 1);
    return cycle(base + 1) + cycle(base + 2) + cycle(base + 3);
}

int simulate(array<int, 2> xs) {
    const auto cycle = [](const int x) -> int { return ((x - 1) % 10) + 1; };

    array<int, 2> ss{};
    int n{};

    while (
        all_of(cbegin(ss), cend(ss), [](const auto a) { return a < 1000; })) {
        const auto rv = roll_value(++n);
        const auto p = (n - 1) % 2;
        const auto score = cycle(xs[p] + rv);

        ss[p] += score;
        xs[p] = score;
    }

    return n * 3 *
           *find_if(cbegin(ss), cend(ss), [](const int a) { return a < 1000; });
}

int main() {
    array<int, 2> xs;
    for (int i = 0; i < 2; ++i) {
        string line;
        getline(cin, line);

        const auto sep = line.find(": ");
        xs[i] = stoi(line.substr(sep + 2));
    }

    cout << simulate(xs) << '\n';
    return 0;
}
