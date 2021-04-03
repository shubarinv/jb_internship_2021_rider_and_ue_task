//
// Created by vhund on 02.04.2021.
//

#ifndef JB_INTSHIP_2021_TRIE_HXX
#define JB_INTSHIP_2021_TRIE_HXX

#include "Node.hxx"

class Trie {
public:
    // Variables

    // Constructors
    Trie() {
        root = new Node();
    }
    explicit Trie(std::string filename) {
        root = new Node();
    }

    // functions
    void addWord(std::string t_word) {
        if (t_word.empty()) {
            std::cerr << "Trie(" << this << ")::addWord(): Attempt to add empty word! (word will be ignored)" << std::endl;
        }
        if (!root->hasChild(t_word[0])) {                    ///< checking if root node has a child node with a value that is equal to first char in given word
            root->children().push_front(new Node(t_word[0]));///< node doesn't have child with required value, so we add it here
        }
        addWord(t_word.substr(1, t_word.size()), root->getChild(t_word[0]));///< by this time we can be sure that there is a child whose val. is equal to word's first character. We will now switch to this child
    }

    void findWord(std::string word) {
        throw std::logic_error("Not implemented");
    }
    bool hasWord(std::string word) {
        throw std::logic_error("Not implemented");
    }

private:
    Node *root{nullptr};

    static void addWord(std::string word, Node *node) {
        if (word[0] == '\0') return;                           ///< Prevents \0 from being added from the end of the word
        if (!word.empty()) {                                   ///< checking if there is anything to add
            if (!node->hasChild(word[0])) {                    ///< checking if current node doesn't have child with value that is same as first char of given word
                node->children().push_front(new Node(word[0]));///< adding missing child
            }
            addWord(word.substr(1, word.size()), node->getChild(word[0]));///< switching to node that has next char from word
        }
    }

};


#endif//JB_INTSHIP_2021_TRIE_HXX
