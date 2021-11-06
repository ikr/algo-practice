struct Solution final {
    int findDuplicate(const vector<int>& xs) const {
        int p1 = xs[0];
        int p2 = xs[xs[0]];

        while (p1 != p2) {
            p1 = xs[p1];
            p2 = xs[xs[p2]];
            
        }
        
        p1 = 0;
        while (p1 != p2) {
            p1 = xs[p1];
            p2 = xs[p2];
        }
        
        return p1;
    }
};
