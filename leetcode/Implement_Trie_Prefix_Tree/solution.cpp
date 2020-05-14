struct Trie final {
    Trie() : m_nodes('z' - 'a' + 1, nullptr) {}
    ~Trie() { for (auto n : m_nodes) delete n; }
    
    void insert(string word) {
        if (word.empty()) return;
        
        const char c = word[0];
        if (word.size() == 1) m_terminal.insert(c);
        if (!m_nodes[c - 'a']) m_nodes[c - 'a'] = new Trie();
        m_nodes[c - 'a']->insert(word.substr(1));
    }
    
    bool search(string word) const {
        const char c = word[0];
        if (word.size() == 1) return m_terminal.count(c);
        if (!m_nodes[c - 'a']) return false;
        return m_nodes[c - 'a']->search(word.substr(1));
    }
    
    bool startsWith(string pre) const {
        if (pre.empty()) return true;
        const char c = pre[0];
        if (!m_nodes[c - 'a']) return false;
        return m_nodes[c - 'a']->startsWith(pre.substr(1));
    }
    
private:
    set<char> m_terminal;
    vector<Trie*> m_nodes;
};
