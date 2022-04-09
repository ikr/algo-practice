#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(deque<bool> A) {
    int os = inof(count(cbegin(A), cend(A), true));
    if (!os) return true;

    bool one = true;
    while (!A.empty()) {
        // cerr << "A:" << A << " one:" << one << endl;

        while (!A.empty() && A.back() != one) A.pop_back();
        if (A.empty()) break;
        if (A.front() == one) return false;
        A.pop_front();
        one = !one;
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    deque<bool> A(N, false);
    for (int i = 0; i < N; ++i) {
        int x;
        cin >> x;
        if (x) A[i] = true;
    }

    cout << (is_possible(move(A)) ? "Yes" : "No") << '\n';
    return 0;
}
