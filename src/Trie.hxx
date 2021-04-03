//
// Created by vhund on 02.04.2021.
//

#ifndef JB_INTSHIP_2021_TRIE_HXX
#define JB_INTSHIP_2021_TRIE_HXX

#include "Node.hxx"
#include <fstream>
#include <future>

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
        if (!root->hasChild(t_word[0])) {                    // checking if root node has a child node with a value that is equal to first char in given word
            root->children().push_front(new Node(t_word[0]));// node doesn't have child with required value, so we add it here
        }
        addWord(t_word.substr(1, t_word.size()), root->getChild(t_word[0]));// by this time we can be sure that there is a child whose val. is equal to word's first character. We will now switch to this child
    }

    void findRecursive(std::string t_word, bool t_useAsync = true) {
        for (auto &child : root->children()) {
            if (t_useAsync) {
                auto tmp = std::async(std::launch::async, findWordRecursive, root, std::move(t_word), "");// using async to speed up search process
            } else {
                findWordRecursive(root, std::move(t_word), "");
            }
        }
    }
    [[maybe_unused]] [[nodiscard]] bool hasWord(std::string word) {
        if (root->hasChild(word[0])) {
            return hasWord(word.substr(1, word.size()), root->getChild(word[0]));
        }
        return false;
    }

    void readFromFile(const std::string& filepath){
        std::ifstream file(filepath);
        if(!file.is_open()) {
            perror("Error open");
            exit(EXIT_FAILURE);
        }

        std::string line;
        while(getline(file, line)) {
            addWord(line);
        }
        file.close();
    }
    Node* getRoot(){
        return root;
    }
private:
    Node *root{nullptr};

    static void addWord(std::string word, Node *node) {
        if (word[0] == '\0') return;                           // Prevents \0 from being added from the end of the word
        if (!word.empty()) {                                   // checking if there is anything to add
            if (!node->hasChild(word[0])) {                    // checking if current node doesn't have child with value that is same as first char of given word
                node->children().push_front(new Node(word[0]));///< adding missing child
            }
            addWord(word.substr(1, word.size()), node->getChild(word[0]));// switching to node that has next char from word
        }
    }

    static void findWordRecursive(Node *node, std::string word, std::string result) {
        if (node == nullptr) {
            std::cerr << "Error: Trie::findWordRecursive: node somewhy empty";
            return;
        }

        if (node->value() != '\0')// prevents root node from being add to resulting string(there will be problems outputting it otherwise)
            result += node->value();

        if (node->value() == word[0])// if value of current node equal word first char, we remove this char from word
            word = word.substr(1, word.size());

        if (node->children().empty() && word.empty()) {// if word was found, and we reached the end of branch
            std::cout << result;
        }
        for (auto &childNode : node->children()) {// recursively going through the trie
            findWordRecursive(childNode, word, result);
        }
    }

    [[nodiscard]] bool hasWord(std::string word, Node *node) {
        if (word[0] == '\0') return true;
        if (node->hasChild(word[0])) {
            return hasWord(word.substr(1, word.size()), node->getChild(word[0]));
        }
        return false;
    }
};


#endif//JB_INTSHIP_2021_TRIE_HXX
