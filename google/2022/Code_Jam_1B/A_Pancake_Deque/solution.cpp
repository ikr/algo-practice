#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int solve(const vector<int> &xs) {
    deque<int> q(cbegin(xs), cend(xs));
    int hi{};
    int result{};

    const auto use_front = [&]() {
        hi = max(hi, q.front());
        q.pop_front();
    };

    const auto use_back = [&]() {
        hi = max(hi, q.back());
        q.pop_back();
    };

    while (!q.empty()) {
        const auto a = q.front();
        const auto b = q.back();

        if (a >= hi && b >= hi) {
            if (a <= b) {
                use_front();
            } else {
                use_back();
            }
            ++result;
        } else if (a >= hi) {
            use_front();
            ++result;
        } else if (b >= hi) {
            use_back();
            ++result;
        } else {
            if (a <= b) {
                use_front();
            } else {
                use_back();
            }
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<int> xs(N);
        for (auto &x : xs) cin >> x;

        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
