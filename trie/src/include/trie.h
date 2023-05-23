#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace trie {

template <typename T>
class TrieNode {
    public:
    explicit TrieNode(char key) {
        m_key = key;
    }

    TrieNode(TrieNode&& other) {
        m_key = other.key;
        m_children = std::move(other.m_children);
    }

    virtual ~TrieNode() = default;

    bool HasChild(char key) const {

    }

    bool HasChidlren() const {

    }

    bool IsEndNode() const { 
        return is_end_;
    }

    bool IsEndNode() const { 
        return is_end_;
    }

    InsertChildNode() {

    }

    GetChildNode() {

    }

    RemoveChildNode() {

    }

    SetEndNode() {

    }

    protected:
    std::unordered_map<char, std::unique_ptr<TrieNode>> m_children;
    char m_key;
    bool m_is_end{false};
};

template <typename T>
class TrieNodeWithValue : public TrieNode {

};

template <typename T>
class Trie {

};
    
}
