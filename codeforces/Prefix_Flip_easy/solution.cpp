#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

template <typename T> constexpr int intof(const T x) {
    return static_cast<int>(x);
}

vector<bool> vectorize(const string &bits) {
    vector<bool> ans(bits.size(), false);
    transform(bits.cbegin(), bits.cend(), ans.begin(),
              [](const char c) { return c == '1'; });
    return ans;
}

vector<bool> invert_reverse(vector<bool> bits, const int prefix_length) {
    transform(bits.begin(), bits.begin() + prefix_length, bits.begin(),
              [](const bool b) { return !b; });
    reverse(bits.begin(), bits.begin() + prefix_length);
    return bits;
}

vector<vector<bool>> adjacent(const vector<bool> &bits) {
    const int sz = bits.size();
    vector<vector<bool>> ans;
    for (int i = 1; i <= sz; ++i) {
        ans.push_back(invert_reverse(bits, i));
    }
    return ans;
}

vi prefix_lengths_sequence(const vector<bool> &a, const vector<bool> &b) {
    if (a == b) return {};

    queue<vector<bool>> q;
    queue<vi> qseq;
    q.push(a);
    qseq.push(vi{});
    unordered_set<vector<bool>> discovered{a};

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        const vi seq = qseq.front();
        qseq.pop();

        const auto adj = adjacent(u);
        const int sz = adj.size();
        for (int i = 1; i <= sz; ++i) {
            const auto v = adj[i - 1];
            if (discovered.count(v)) continue;

            vi nseq = seq;
            nseq.push_back(i);
            if (v == b) return nseq;

            discovered.insert(v);
            q.push(v);
            qseq.push(nseq);
        }
    }

    return {};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int sz;
        cin >> sz;

        string a;
        string b;
        cin >> a >> b;

        assert(intof(a.size()) == sz);
        assert(intof(b.size()) == sz);

        const auto ans = prefix_lengths_sequence(vectorize(a), vectorize(b));
        cout << ans.size();
        for (const auto l : ans) {
            cout << ' ' << l;
        }
        cout << '\n';
    }

    return 0;
}
