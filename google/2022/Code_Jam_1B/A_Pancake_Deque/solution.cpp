#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int solve(const vector<int> &xs) {
    const auto n = sz(xs);
    assert(n <= 20);
    int result{};

    for (int bits = 0; bits < (1 << n); ++bits) {
        vector<bool> frts(n, false);
        for (int j = 0; j < n; ++j) {
            if (bits & (1 << j)) frts[j] = true;
        }

        int candidate{};
        deque<int> q(cbegin(xs), cend(xs));
        int hi{};

        const auto use_front = [&]() {
            hi = max(hi, q.front());
            q.pop_front();
        };

        const auto use_back = [&]() {
            hi = max(hi, q.back());
            q.pop_back();
        };

        for (const auto f : frts) {
            assert(!q.empty());

            if (f) {
                if (q.front() >= hi) ++candidate;
                use_front();
            } else {
                if (q.back() >= hi) ++candidate;
                use_back();
            }
        }

        result = max(result, candidate);
        assert(q.empty());
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
