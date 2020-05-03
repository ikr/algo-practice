struct Solution final {
    bool canConstruct(const string &n, const string &m) const {
        unordered_map<char, int> letter_counts;
        for (const char l : m) letter_counts[l]++;
        
        for (const char l : n) {
            letter_counts[l]--;
            if (letter_counts[l] < 0) return false;
        }
        
        return true;
    }
};
