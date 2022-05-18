#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int num_frames(const vector<int> &A) {
    int cur{};
    int result{};

    for (const auto x : A) {
        if (x != cur) {
            cur = x;
            ++result;
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        vector<int> A(N);
        for (auto &x : A) cin >> x;

        cout << num_frames(A) << '\n';
    }

    return 0;
}
