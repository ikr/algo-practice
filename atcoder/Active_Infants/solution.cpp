#include <bits/stdc++.h>

using namespace std;

template <typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';

    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    os << ']';
    return os;
}


using Int = long long;

int main() {
    int n;
    cin >> n;
    
    vector<int> xs(n, 0);
    for (auto &x : xs) {
        cin >> x;
    }
    
    vector<pair<int, pair<int, int>>> win_pair_heap;
    
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            const int win = (j - i) * (xs[i] + xs[j]);
            win_pair_heap.push_back({win, {i, j}});
            push_heap(win_pair_heap.begin(), win_pair_heap.end());
        }
    }
    
    cout << win_pair_heap << endl;
    
    unordered_set<int> used_idc;
    Int ans = 0;
    
    while (!win_pair_heap.empty() && used_idc.size() < n) {
        const auto [win, pr] = win_pair_heap.front();
        const auto [i, j] = pr;
        
        if (!used_idc.count(i) && !used_idc.count(j)) { 
            ans += win;
            used_idc.insert(i);
            used_idc.insert(j);
        }
        
        pop_heap(win_pair_heap.begin(), win_pair_heap.end());
        win_pair_heap.pop_back();
    }
    
    cout << ans << endl;
    
    return 0;
}
