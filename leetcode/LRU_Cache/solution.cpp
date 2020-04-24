struct LRUCache final {
    LRUCache(const int capacity) : m_capacity{capacity} {}
    
    int get(const int key) {
        if (!m_values_by_key.count(key)) return -1;
        
        const int old_usage = m_usages_by_key[key];
        const auto [first, last] = m_keys_by_usage.equal_range(old_usage);
        auto it_to_erase = m_keys_by_usage.cend();
        for (auto it = first; it != last; ++it) {
            const auto [u, k] = *it;
            
            if (k == key) {
                it_to_erase = it;
                break;
            }
        }
        
        assert(it_to_erase != m_keys_by_usage.cend());
        m_keys_by_usage.erase(it_to_erase);
        m_keys_by_usage.emplace(old_usage + 1, key);
        
        m_usages_by_key[key]++;
        return m_values_by_key.at(key);
    }
    
    void put(const int key, const int value) {
        if (m_values_by_key.count(key)) return;
        
        if (m_values_by_key.size() == m_capacity) {
            assert(!m_keys_by_usage.empty());
            const auto [u, k] = *m_keys_by_usage.cbegin();
            m_keys_by_usage.erase(m_keys_by_usage.cbegin());
            m_usages_by_key.erase(k);
            m_values_by_key.erase(k);
        }
        
        m_values_by_key[key] = value;
        m_keys_by_usage.emplace(0, key);
    }
    
private:
    const int m_capacity;

    unordered_map<int, int> m_usages_by_key;
    multimap<int, int> m_keys_by_usage;
    unordered_map<int, int> m_values_by_key;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
