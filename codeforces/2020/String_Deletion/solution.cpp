#include <bits/stdc++.h>
using namespace std;
using Iter = deque<int>::iterator;

deque<int> seg_lengths(const string &ds) {
    const int n = ds.size();

    deque<int> ans;
    char curr = ds[0];
    int l = 1;

    for (int i = 1; i < n; ++i) {
        if (ds[i] != curr) {
            ans.push_back(l);
            curr = ds[i];
            l = 1;
        } else {
            ++l;
        }
    }

    ans.push_back(l);
    return ans;
}

void perform_op(deque<int> &xs, Iter &it) {
    assert(!xs.empty());

    const auto advance = [&]() {
        it = find_if(it, end(xs), [](const int x) { return x > 1; });
    };

    if (it != end(xs)) {
        --(*it);
        advance();
    } else {
        xs.pop_front();
    }

    if (!xs.empty()) {
        if (it == begin(xs)) {
            ++it;
            advance();
        }

        xs.pop_front();
    }
}

int max_ops(const string &ds) {
    auto ls = seg_lengths(ds);
    auto it = find_if(begin(ls), end(ls), [](const int x) { return x > 1; });
    int ans = 0;

    while (!ls.empty()) {
        perform_op(ls, it);
        ++ans;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string ds(n, ' ');
        cin >> ds;

        cout << max_ops(ds) << '\n';
    }

    return 0;
}
