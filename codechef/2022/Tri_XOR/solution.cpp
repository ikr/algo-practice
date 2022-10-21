#include <bits/stdc++.h>
using namespace std;

using tri = tuple<int, int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

struct ThreeStash final {
    void push(const int x) {
        if (sz(xs) < 3) xs.push_back(x);
    }

    int pop() {
        assert(!xs.empty());
        const auto result = xs.back();
        xs.pop_back();
        return result;
    }

  private:
    vector<int> xs;
};

vector<tri> find_program(multiset<int> xs) {
    vector<tri> result;

    const auto deal_with_zero_off_rest = [&](vector<int> one,
                                             ThreeStash zer) -> void {
        assert(!one.empty());
        while (sz(one) < 3) {
            const auto za = zer.pop();
            const auto zb = zer.pop();

            const auto x = one.back();
            one.pop_back();

            for (const auto y : {za, zb, x}) {
                const auto it = xs.find(y);
                assert(it != cend(xs));
                xs.erase(it);
            }

            result.emplace_back(za, zb, x);

            xs.insert(x ^ za);
            one.push_back(x ^ za);

            xs.insert(x ^ zb);
            one.push_back(x ^ zb);

            xs.insert(za ^ zb);
            zer.push(za ^ zb);
        }

        for (const auto y : one) {
            const auto it = xs.find(y);
            assert(it != cend(xs));
            xs.erase(it);
        }

        result.emplace_back(one[0], one[1], one[2]);

        xs.insert(one[0] ^ one[1]);
        xs.insert(one[1] ^ one[2]);
        xs.insert(one[0] ^ one[2]);
    };

    const auto zero_off_bit = [&](const int bit_shift) -> void {
        const int mask = 1 << bit_shift;
        vector<int> one;
        ThreeStash zer;

        for (const auto x : xs) {
            if (x & mask) {
                one.push_back(x);
            } else {
                zer.push(x);
            }
        }

        if (one.empty()) return;

        vector<int> rest;
        while (sz(one) % 3) {
            rest.push_back(one.back());
            one.pop_back();
        }

        for (auto i = 0; i < sz(one); i += 3) {
            for (int j = 0; j < 3; ++j) {
                assert(i + j < sz(one));
                const auto it = xs.find(one[i + j]);
                assert(it != cend(xs));

                xs.erase(it);
            }

            result.emplace_back(one[i], one[i + 1], one[i + 2]);

            xs.insert(one[i] ^ one[i + 1]);
            zer.push(one[i] ^ one[i + 1]);

            xs.insert(one[i + 1] ^ one[i + 2]);
            zer.push(one[i + 1] ^ one[i + 2]);

            xs.insert(one[i] ^ one[i + 2]);
            zer.push(one[i] ^ one[i + 2]);
        }

        if (!rest.empty()) {
            deal_with_zero_off_rest(move(rest), move(zer));
        }
    };

    for (int bs = 31; bs >= 0; --bs) {
        zero_off_bit(bs);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            if (x) xs.push_back(x);
        }

        const auto ops = find_program(multiset<int>(crbegin(xs), crend(xs)));
        cout << sz(ops) << '\n';
        for (const auto &[a, b, c] : ops) {
            cout << a << ' ' << b << ' ' << c << '\n';
        }
    }

    return 0;
}
