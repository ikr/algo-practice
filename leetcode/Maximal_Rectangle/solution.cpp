using vi = vector<int>;
using vc = vector<char>;

int max_hist_rect_area(const vi &hs) {
    int ans = 0;
    stack<int> loidx;

    for (int j = 0; j != hs.size();) {
        if (loidx.empty() || hs[loidx.top()] < hs[j]) {
            loidx.push(j);
            ++j;
        } else {
            const int k = loidx.top();
            loidx.pop();
            ans = max(ans, hs[k] * (loidx.empty() ? j : j - loidx.top() - 1));
        }
    }

    while (!loidx.empty()) {
        const int j = hs.size() - 1;
        const int k = loidx.top();
        loidx.pop();
        ans = max(ans, hs[k] * (loidx.empty() ? j + 1 : j - loidx.top()));
    }

    return ans;
}

struct Solution final {
    int maximalRectangle(const vector<vc> &rows) const {
        const int H = rows.size();
        if (!H) return 0;
        const int W = rows[0].size();
        if (!W) return 0;
        
        int ans = 0;
        vi hs(W, 0);
        
        for (const auto &row : rows) {
            for (int c = 0; c != W; ++c) {
                if (row[c] == '0') hs[c] = 0;
                else ++hs[c]; 
            }
            
            ans = max(ans, max_hist_rect_area(hs));
        }
        
        return ans;
    }
};
