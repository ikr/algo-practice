class Solution {
public:
    
    int maxPower(string s) {
        int ans = 0;
        int cnt = 0;
        char last = 0;
        
        for (const char c : s) {
            if (c != last) {
                ans = max(cnt, ans);
                last = c;
                cnt = 1;
            } else {
                ++cnt;
            }
        }
        
        ans = max(ans, cnt);
        
        return ans;
    }
};
