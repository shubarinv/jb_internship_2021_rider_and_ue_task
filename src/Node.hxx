//
// Created by vhundef on 02.04.2021.
//

#ifndef JB_INTSHIP_2021_NODE_HXX
#define JB_INTSHIP_2021_NODE_HXX

#include <algorithm>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>

class Node {
public:
    Node() {
        m_value = "";///< the only way this to happen, is for Node to be in root of the Trie
    }
    explicit Node(std::string value) : m_value(std::move(value)) {}
    explicit Node(char value) : m_value(std::string(1, value)) {}

    [[nodiscard]] std::string value() const {
        return m_value;
    }

    void setValue(std::string newValue) {
        m_value = std::move(newValue);
    }

    std::forward_list<std::unique_ptr<Node>> &children() {
        return m_children;
    }

    Node *getChild(const std::string &t_childToLookFor) {
        for (auto &child : m_children) {
            if (child->value() == t_childToLookFor) { return child.get(); }
        }
        return nullptr;
    }
    Node *getChild(char &t_childToLookFor) {
        for (auto &child : m_children) {
            if (child->value().size() == 1 && child->value()[0] == t_childToLookFor) { return child.get(); }
        }
        return nullptr;
    }

    bool hasChild(std::string &t_childToLookFor) {
        return getChild(t_childToLookFor) != nullptr;
    }
    bool hasChild(char &t_childToLookFor) {
        return getChild(t_childToLookFor) != nullptr;
    }
    void setChildren(std::forward_list<std::unique_ptr<Node>> newChildrenList) {
        m_children = std::move(newChildrenList);
    }

private:
    std::string m_value;
    std::forward_list<std::unique_ptr<Node>> m_children;///< holds pointers for children nodes.
};

#endif//JB_INTSHIP_2021_NODE_HXX