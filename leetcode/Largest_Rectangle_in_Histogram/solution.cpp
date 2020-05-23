using vi = vector<int>;

struct Solution final {
    int largestRectangleArea(const vi &hs) {
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
};
