#include <bits/stdc++.h>

using namespace std;

constexpr int SIZE = 200000;

template <typename T> struct RndInt final {
    RndInt(const T lo, const T hi) : m_gen{random_device{}()}, m_dist{lo, hi} {}
    T next() { return m_dist(m_gen); }

  private:
    mt19937 m_gen;
    uniform_int_distribution<T> m_dist;
};

int main() {
    cout << SIZE << ' ' << SIZE << ' ' << SIZE << ' ' << SIZE << '\n';

    RndInt ur{1, SIZE};
    for (int i = 1; i <= SIZE; ++i) cout << i << ' ' << ur.next() << '\n';

    for (int i = 1; i <= SIZE; ++i) {
        if (i > 1) cout << ' ';
        cout << i;
    }

    cout << '\n';
    return 0;
}
