struct LRUCache final {
    LRUCache(const int capacity) : m_capacity{capacity} {}
    
    int get(const int key) {
        if (!m_values_by_key.count(key)) return -1;
        
        const auto it = find(m_keys.cbegin(), m_keys.cend(), key);
        m_keys.erase(it);
        m_keys.push_front(key);
        
        return m_values_by_key.at(key);
    }
    
    void put(const int key, const int value) {
        if (m_values_by_key.size() == m_capacity && !m_values_by_key.count(key)) {
            assert(!m_keys.empty());
            m_values_by_key.erase(m_keys.back());
            m_keys.pop_back();
        }
        
        if (m_values_by_key.count(key)) {
            const auto it = find(m_keys.cbegin(), m_keys.cend(), key);
            m_keys.erase(it);
        }
        
        m_keys.push_front(key);
        m_values_by_key[key] = value;
    }
    
private:
    const int m_capacity;
    deque<int> m_keys;
    unordered_map<int, int> m_values_by_key;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
