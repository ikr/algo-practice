#include <bits/stdc++.h>

using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';

    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    os << ']';
    return os;
}

struct Tower final {
    int left;
    int right;
    int height;
    
    Tower(const vector<int> &src): left{src[0]}, right{src[1]}, height{src[2]} {}
};

map<int, vector<Tower>> gather_key_xs(const vector<vector<int>> &towers) {
    map<int, vector<Tower>> ans;
    
    for (const auto &t : towers) {
        const int left = t[0];
        const int right = t[1];
            
        ans.emplace(left, vector<Tower>{});
        ans.emplace(right, vector<Tower>{});
    }
    
    return ans;
}

struct TowersLess final {
    bool operator()(const Tower &lhs, const Tower &rhs) const {
        return lhs.height < rhs.height;
    }
};

void gather_tower_heaps_by_x(const vector<vector<int>> &towers, map<int, vector<Tower>> &key_xs) {
    for (const auto &tsrc : towers) {
        const Tower t(tsrc);
        
        for (auto it = key_xs.lower_bound(t.left); it != key_xs.end() && it->first <= t.right; ++it) {
            it->second.push_back(t);
            push_heap(it->second.begin(), it->second.end(), TowersLess{});
        }
    }
}

Tower pop(vector<Tower> &heap) {
    pop_heap(heap.begin(), heap.end(), TowersLess{});
    Tower ans = heap.back();
    heap.pop_back();
    return ans;
}

void supplement(vector<vector<int>> &skyline, const int x, const int h) {
    if (skyline.empty() && !h) return;
    if (skyline.size() && h == skyline.back()[1]) return;
    skyline.push_back({x, h});
}

struct Solution final {
    vector<vector<int>> getSkyline(const vector<vector<int>> &towers) const {
        auto tower_heaps_by_x = gather_key_xs(towers);
        gather_tower_heaps_by_x(towers, tower_heaps_by_x);
        
        vector<vector<int>> ans;
        
        for (auto [x, heap] : tower_heaps_by_x) {
            const Tower dom = pop(heap);            
            optional<Tower> sub = heap.size() ? optional<Tower>{pop(heap)} : nullopt;
            
            if (x != dom.left && x != dom.right) {
                supplement(ans, x, dom.height);
            } else if (x == dom.left) {
                if (sub) supplement(ans, x, sub->height);    
                else supplement(ans, x, 0);
                
                supplement(ans, x, dom.height);
            } else {
                assert(x == dom.right);
                supplement(ans, x, dom.height);
                
                if (sub) supplement(ans, x, sub->height);    
                else supplement(ans, x, 0);
            }
        }
        
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    const auto actual = Solution{}.getSkyline(
        vector<vector<int>>{{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}});
                                                                  
    const vector<vector<int>> expected{{2, 10}, {3, 15}, {7, 12}, {12, 0}, {15, 10}, {20, 8}, {24, 0}};
    
    cout << actual << '\n' << expected << endl;
                                                                  
    assert(actual == expected);
    
    return 0;
}
