#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> construct_A(const int W) {
    vector<int> result;

    const auto recur = [&](const auto self, const int n) -> void {
        if (n == 0) return;

        if (n / 3) {
            result.push_back(n / 3);
            result.push_back(n / 3);
            result.push_back(n / 3);
            self(self, n / 3 - 1);
        } else if (n / 2) {
            result.push_back(n / 2);
            result.push_back(n / 2);
            self(self, n / 2 - 1);
        } else {
            result.push_back(n)
        }
    };

    recur(recur, W);
    sort(begin(result), end(result));
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int W;
    cin >> W;

    const auto A = construct_A(W);
    cout << sz(A) << '\n' << A << '\n';
    return 0;
}
