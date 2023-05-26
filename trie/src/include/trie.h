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
    
    ~TrieNodeTerminal() override = default;
    
    T GetValue() const {
        return m_value;
    }

    private:
    T m_value;
};

template <typename T>
class Trie {
    public:
    /**
   * TODO(P0): Add implementation
   *
   * @brief Construct a new Trie object. Initialize the root node with '\0'
   * character.
   */
  Trie() {
    root_ = std::make_unique<TrieNode>('\0');
  };

  /**
   * @brief Insert key-value pair into the trie.
   *
   * If the key is an empty string, return false immediately.
   *
   * If the key already exists, return false. Duplicated keys are not allowed and
   * you should never overwrite value of an existing key.
   *
   * When you reach the ending character of a key:
   * 1. If TrieNode with this ending character does not exist, create new TrieNodeWithValue
   * and add it to parent node's children_ map.
   * 2. If the terminal node is a TrieNode, then convert it into TrieNodeWithValue by
   * invoking the appropriate constructor.
   * 3. If it is already a TrieNodeWithValue,
   * then insertion fails and returns false. Do not overwrite existing data with new data.
   *
   * You can quickly check whether a TrieNode pointer holds TrieNode or TrieNodeWithValue
   * by checking the is_end_ flag. If is_end_ == false, then it points to TrieNode. If
   * is_end_ == true, it points to TrieNodeWithValue.
   *
   * @param key Key used to traverse the trie and find the correct node
   * @param value Value to be inserted
   * @return True if insertion succeeds, false if the key already exists
   */
  template <typename T>
  bool Insert(const std::string &key, T value) {
    
  }

  /**
   * @brief Remove key value pair from the trie.
   * This function should also remove nodes that are no longer part of another
   * key. If key is empty or not found, return false.
   *
   * You should:
   * 1) Find the terminal node for the given key.
   * 2) If this terminal node does not have any children, remove it from its
   * parent's children_ map.
   * 3) Recursively remove nodes that have no children and are not terminal node
   * of another key.
   *
   * @param key Key used to traverse the trie and find the correct node
   * @return True if the key exists and is removed, false otherwise
   */
  bool Remove(const std::string &key) { 
  
  }

bool remove_inner(const std::string &key, size_t i, std::unique_ptr<TrieNode> *curr, bool *success) {

}
  /**
   * @brief Get the corresponding value of type T given its key.
   * If key is empty, set success to false.
   * If key does not exist in trie, set success to false.
   * If the given type T is not the same as the value type stored in TrieNodeWithValue
   * (ie. GetValue<int> is called but terminal node holds std::string),
   * set success to false.
   *
   * To check whether the two types are the same, dynamic_cast
   * the terminal TrieNode to TrieNodeWithValue<T>. If the casted result
   * is not nullptr, then type T is the correct type.
   *
   * @param key Key used to traverse the trie and find the correct node
   * @param success Whether GetValue is successful or not
   * @return Value of type T if type matches
   */
  template <typename T>
  T GetValue(const std::string &key, bool *success) {
    
  }
  private:
  /* Root node of the trie */
  std::unique_ptr<TrieNode> m_root;
  /* Read-write lock for the trie */
  std::shared_mutex mutex_;
};
    
}
