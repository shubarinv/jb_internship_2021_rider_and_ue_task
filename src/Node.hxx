//
// Created by vhundef on 02.04.2021.
//

#ifndef JB_INTSHIP_2021_NODE_HXX
#define JB_INTSHIP_2021_NODE_HXX

#include <algorithm>
#include <forward_list>
#include <iterator>

class Node {
public:
    Node() {
        m_value = '\0';///< the only way this to happen, is for Node to be in root of the Trie
    }
    [[nodiscard]] char value() const {
        return m_value;
    }

    Node *getChild(char &t_childToLookFor) {
        for (auto &child : m_children) {
            if (child->value() == t_childToLookFor) { return child; }
        }
    }
    bool hasChild(char &t_childToLookFor) {
        for (auto &child : m_children) {
            if (child->value() == t_childToLookFor)
                return true;
        }
        return false;
    }

private:
    char m_value = '\0';
    std::forward_list<Node *> m_children;///< holds pointers for children nodes.
};


#endif//JB_INTSHIP_2021_NODE_HXX