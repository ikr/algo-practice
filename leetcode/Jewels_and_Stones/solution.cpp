struct Solution final {
    int numJewelsInStones(const string &js, const string &ss) const {
        const unordered_set<char> jewels(js.cbegin(), js.cend());
        return count_if(ss.cbegin(), ss.cend(), [&jewels](const char stone) { return jewels.count(stone); });
    }
};
