//
// Created by vhundef on 02.04.2021.
//

#ifndef JB_INTSHIP_2021_NODE_HXX
#define JB_INTSHIP_2021_NODE_HXX

#include <algorithm>
#include <forward_list>
#include <iostream>
#include <iterator>

class Node {
public:
    Node() {
        m_value = '\0';///< the only way this to happen, is for Node to be in root of the Trie
    }
    explicit Node(char value) : m_value(value){}

    [[nodiscard]] char value() const {
        return m_value;
    }

    std::forward_list<Node *>& children() {
        return m_children;
    }

    Node *getChild(char t_childToLookFor) {
        for (auto &child : m_children) {
            if (child->value() == t_childToLookFor) { return child; }
        }
        return nullptr;
    }
    bool hasChild(char &t_childToLookFor) {
        return getChild(t_childToLookFor) != nullptr;
    }

private:
    char m_value = '\0';
    std::forward_list<Node *> m_children;///< holds pointers for children nodes.
};


#endif//JB_INTSHIP_2021_NODE_HXX
