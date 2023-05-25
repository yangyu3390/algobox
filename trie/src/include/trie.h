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
        return m_children.count(key)>0;
    }

    bool HasChidlren() const {
        return m_children.size()>0;
    }

    bool IsEndNode() const { 
        return m_is_end;
    }
/**
   * @brief Return key of this trie node.
   *
   * @return m_key of this trie node.
   */
  char GetKey() const { return m_key; }

  /**
   * @brief Insert a child node for this trie node into m_children map, given the key and
   * unique_ptr of the child node. If specified key already exists in m_children,
   * return nullptr. If parameter `child`'s key is different than parameter
   * `key`, return nullptr.
   *
   * Note that parameter `child` is rvalue and should be moved when it is
   * inserted into children_map.
   *
   * The return value is a pointer to unique_ptr because pointer to unique_ptr can access the
   * underlying data without taking ownership of the unique_ptr. Further, we can set the return
   * value to nullptr when error occurs.
   *
   * @param key Key of child node
   * @param child Unique pointer created for the child node. This should be added to m_children map.
   * @return Pointer to unique_ptr of the inserted child node. If insertion fails, return nullptr.
   */
    std::unique_ptr<TrieNode>* InsertChildNode(char key, std::unique_ptr<TrieNode>&& child) {
        if (key != child->GetKey()) return nullptr;
        if (HasChild(key)) return nullptr;
        m_children[key] = std::forward<unique_ptr<TrieNode>>(child);
        return &m_children[key];
    }
   /**
   * @brief Get the child node given its key. If child node for given key does
   * not exist, return nullptr.
   *
   * @param key Key of child node
   * @return Pointer to unique_ptr of the child node, nullptr if child
   *         node does not exist.
   */
    std::unique_ptr<TrieNode>* GetChildNode(char key) {
        if (m_children.count(key)==0) return nullptr;
        return &m_children[key];
    }
   /**
   * @brief Remove child node from m_children map.
   * If key does not exist in m_children, return immediately.
   *
   * @param key Key char of child node to be removed
   */
    void RemoveChildNode(char key) {
        if (m_children.count(key)==0) return;
        m_children.erase(key);
    }
   /**
   * @brief Set the is_end_ flag to true or false.
   *
   * @param is_end Whether this trie node is ending char of a key string
   */
    void SetEndNode(bool is_end) {
        m_is_end = is_end;
    }

    protected:
    std::unordered_map<char, std::unique_ptr<TrieNode>> m_children;
    char m_key;
    bool m_is_end{false};
};

template <typename T>
class TrieNodeTerminal : public TrieNode {
    public:
    /**
     * @brief convert TrieNode to TrieNodeTerminal. TrieNodeTerminal is used to store a trie node with value
     * 
    */
    TrieNodeTerminal(char key, T value): TrieNode(key), m_value(value) {
        m_is_end = true;
    }
    TrieNodeTerminal(TrieNode&& other, T value): TrieNode(std::forward<TrieNode>(other)), m_value(value) {
        m_is_end = true;
    }
    ~TrieNodeTerminal()=default;
    private:
    T m_value;
};

template <typename T>
class Trie {

};
    
}
