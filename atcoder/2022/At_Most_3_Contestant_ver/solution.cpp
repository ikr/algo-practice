#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> construct_A(const int W) {
    vector<int> result{W};
    for (int i = 1; i <= 99; ++i) {
        result.push_back(i);
        result.push_back(i * 100);
        result.push_back(i * 100 * 100);
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int W;
    cin >> W;

    const auto A = construct_A(W);
    cout << A.size() << '\n' << A << '\n';
    return 0;
}
