#include <bits/stdc++.h>

using namespace std;

using Vec = vector<int>;
using Iter = Vec::iterator;

pair<Iter, int> capacity_edge(Iter first, Iter last) {
    Iter it = upper_bound(first, last, *first);
    return it == last ? make_pair(it, INT_MAX) : make_pair(it, *it - *first);
}

int compute(const Iter first, const Iter last, int source) {
    Iter edge = first;

    while (source) {
        auto [it, capacity] = capacity_edge(edge, last);
        const int radius = distance(first, it);
        if (source < radius) break;
        const int delta = min(capacity, source / radius);

        if (it == last) {
            *first += delta;
            break;
        }

        transform(first, it, first, [delta](const int x) { return x + delta; });
        source -= radius * delta;
        edge = it;
    }

    return *first;
}

int main() {
    int n;
    int k;
    cin >> n >> k;

    Vec xs(n);
    for (auto &x : xs) {
        cin >> x;
    }

    sort(begin(xs), end(xs));
    copy(cbegin(xs) + xs.size() / 2, cend(xs), begin(xs));
    xs.resize(xs.size() / 2 + 1);

    cout << compute(begin(xs), end(xs), k) << '\n';
}
