void pad_left(string &ds) {
    if (ds[0] == '0') {
        ds.erase(
            ds.cbegin(), 
            find_if(ds.cbegin(), ds.cend(), [](const char c) { return c != '0'; })
        );
    }
    
    if (ds.empty()) ds = "0";
}

struct Solution final {
    string removeKdigits(string ds, int k) const {
        if (k == ds.size()) return "0";
        
        for (int i = 0; i < ds.size() && k > 0;) {
            const char d = ds[i];
            if (d == '0') {
                ++i;
                continue;
            }
            
            char lo = d;
            for (int j = i + 1; j < min(static_cast<int>(ds.size()), i + k + 1); ++j) {
                if (ds[j] < lo) {
                    lo = ds[j];
                    break;
                }
            }
            
            if (lo < d || i == ds.size() - 1) {
                --k;
                ds.erase(i, 1);
            } else ++i;
        }
        
        if (k > 0) {
            ds.erase(ds.size() - k);
        }
        
        pad_left(ds);
        return ds;
    }
};
