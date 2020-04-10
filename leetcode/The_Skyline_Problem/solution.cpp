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

struct TowersGreater final {
    bool operator()(const Tower &lhs, const Tower &rhs) const {
        const pair<int, pair<int, int>> lhs_tuple{lhs.height, {lhs.left, lhs.right}};
        const pair<int, pair<int, int>> rhs_tuple{rhs.height, {rhs.left, rhs.right}};
        
        return lhs_tuple > rhs_tuple;
    }
};

void supplement(vector<vector<int>> &skyline, const int x, const int h) {
    if (skyline.size() && h == skyline.back()[1]) return;
    skyline.push_back({x, h});
}

struct Solution final {
    vector<vector<int>> getSkyline(const vector<vector<int>> &towers_src) const {
        set<int> xs;
        unordered_multimap<int, Tower> towers_by_left;
        unordered_multimap<int, Tower> towers_by_right;
        for (const auto &src : towers_src) {
            const Tower t(src);
            
            xs.insert(t.left);
            xs.insert(t.right);
            
            towers_by_left.emplace(t.left, t);
            towers_by_right.emplace(t.right, t);
        }
        
        vector<vector<int>> ans;
        set<Tower, TowersGreater> curr;
        for (const int x : xs) {
            const auto [rfirst, rlast] = towers_by_right.equal_range(x);
            for (auto it = rfirst; it != rlast; ++it) {
                curr.erase(it->second);
            }
            
            const auto [lfirst, llast] = towers_by_left.equal_range(x);
            for (auto it = lfirst; it != llast; ++it) {
                curr.insert(it->second);
            }
            
            if (curr.empty()) supplement(ans, x, 0);
            else supplement(ans, x, curr.begin()->height);
        }
        
        return ans;
    }
};

vector<vector<int>> pyramid(const int sz) {
    vector<vector<int>> ans;
    
    for (int i = 0; i != sz / 2; ++i) {
        ans.push_back({i, sz - i - 1, i + 1});
    }
    
    return ans;
}

vector<vector<int>> concentric_top_down(const int sz) {
    vector<vector<int>> ans;
    
    for (int i = 0; i != sz; ++i) {
        ans.push_back({i, sz, sz - i});
    }
    
    return ans;
}

struct TestCase final {
    const vector<vector<int>> input;
    const vector<vector<int>> expected_answer;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    const vector<TestCase> testCases{
        {
            {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}},
            {{2, 10}, {3, 15}, {7, 12}, {12, 0}, {15, 10}, {20, 8}, {24, 0}}
        },
        {
            {{1,2,1},{1,2,2},{1,2,3}},
            {{1,3},{2,0}}
        },
        {
            {{0,5,7},{5,10,7},{5,10,12},{10,15,7},{15,20,7},{15,20,12},{20,25,7}},
            {{0,7},{5,12},{10,7},{15,12},{20,7},{25,0}}
        },
        {
            {{2,7,1},{3,6,2},{4,5,3}},
            {{2,1},{3,2},{4,3},{5,2},{6,1},{7,0}}
        },
        {
            {{3,7,8},{3,8,7},{3,9,6},{3,10,5},{3,11,4},{3,12,3},{3,13,2},{3,14,1}},
            {{3,8},{7,7},{8,6},{9,5},{10,4},{11,3},{12,2},{13,1},{14,0}}
        }
    };
    
    for (const auto [input, expected] : testCases) {
        const auto actual = Solution{}.getSkyline(input);
        cout << "ACT " << actual << "\nEXP " << expected << '\n' << endl;
        assert(actual == expected);
    }
    
    auto t0 = chrono::steady_clock::now();
    Solution{}.getSkyline(pyramid(4000));    
    auto t1 = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds> (t1 - t0).count();
    cout << "Pyramid " << elapsed_ms << " ms\n";
    
    t0 = chrono::steady_clock::now();
    Solution{}.getSkyline(concentric_top_down(10000));    
    t1 = chrono::steady_clock::now();
    elapsed_ms = chrono::duration_cast<std::chrono::milliseconds> (t1 - t0).count();
    cout << "CTD " << elapsed_ms << " ms\n";
    
    return 0;
}
