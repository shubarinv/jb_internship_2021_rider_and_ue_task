//
// Created by vhund on 10.04.2021.
//

#ifndef JB_INTSHIP_2021_COMPRESSEDTRIE_HXX
#define JB_INTSHIP_2021_COMPRESSEDTRIE_HXX

#include "Node.hxx"
#include <fstream>
#include <future>
#include <memory>

class CompressedTrie {
private:
public:
    // Constructors
    CompressedTrie() {
        root = std::make_shared<Node>();
    }


    // functions

    /**
     * @brief adds specified word to data structure
     * @param t_word word to add
     */
    [[maybe_unused]] void addWord(std::string t_word) {
        if (t_word.empty()) {
            std::cerr << "Trie(" << this << ")::addWord(): Attempt to add empty word! (word will be ignored)" << std::endl;
            return;
        }
        if (!root->hasChild(t_word[0])) {                                  // checking if root node has a child node with a value that is equal to first char in given word
            root->children().push_front(std::make_unique<Node>(t_word[0]));// node doesn't have child with required value, so we add it here
        }
        addWord(t_word.substr(1, t_word.size()), root->getChild(t_word[0]));// by this time we can be sure that there is a child whose val. is equal to word's first character. We will now switch to this child
    }

    /**
     * @brief recursively goes through the data structure and looks for specified combination of symbols
     * @param t_word combination of symbols
     * @param t_useAsync whether to use async
     */
    [[maybe_unused]] void findRecursive(const std::string &t_word, SafeList<std::string> *queue) {
        stopAsync = false;
        for (auto &child : root->children()) {
            pending_futures.push_back(std::async(std::launch::async, findWordRecursive, child.get(), t_word, "", queue, &stopAsync));// using async to speed up search process
        }
    }
    /**
     * @brief looks for specified word; starts looking from data structure's root
     * @param word word to look for
     * @return
     */
    [[maybe_unused]] [[nodiscard]] bool hasWord(std::string word) {
        for (auto &chr : root->value()) {
            if (chr == word[0])
                word = word.substr(1, word.size());
        }
        if (root->hasChild(word[0])) {
            return hasWord(word.substr(1, word.size()), root->getChild(word[0]));
        }
        return false;
    }

    /**
     * @brief reads words from specified file
     * @param filepath path to the file you want to read from.
     */
    [[maybe_unused]] void readFromFile(const std::string &filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            perror("Error open");
            exit(EXIT_FAILURE);
        }

        std::string line;
        while (getline(file, line)) {
            addWord(line);
        }
        file.close();
    }
    [[maybe_unused]] Node *getRoot() {
        return root.get();
    }

    void compress() {
        compressTrie(root.get());
    }
    void cancelAsync() {
        stopAsync = true;
        for (auto &task : pending_futures) {
            while (!checkIfAsyncTaskFinished(task)) {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(10ns);
            }
        }
        pending_futures.clear();
    }

private:
    std::shared_ptr<Node> root{nullptr};
    bool stopAsync{false};
    std::vector<std::future<void>> pending_futures;
    /**
     * @brief Adds word to data structure
     * @param word word to add
     * @param node pointer to the node you want to add the word to
     */
    static void addWord(std::string word, Node *node) {
        if (word[0] == '\0') return;                                            // Prevents \0 from being added from the end of the word
        if (!word.empty()) {                                                    // checking if there is anything to add
            if (!node->hasChild(word[0])) {                                     // checking if current node doesn't have child with value that is same as first char of given word
                node->children().emplace_front(std::make_unique<Node>(word[0]));///< adding missing child
            }
            addWord(word.substr(1, word.size()), node->getChild(word[0]));// switching to node that has next char from word
        }
    }

    /**
     * @brief looks for specified word in beginning of other words
     * @param word word to look for
     * @param node pointer to current node
     * @return
     */
    [[nodiscard]] static bool hasWord(std::string word, Node *node) {
        if (word[0] == '\0') return true;
        for (auto &chr : node->value()) {
            if (chr == word[0])
                word = word.substr(1, word.size());
        }
        return hasWord(word.substr(1, word.size()), node->getChild(word[0]));
    }
    static void compressTrie(Node *node) {
        int childrenCount = 0;
        for (auto &child : node->children()) {
            childrenCount++;
        }
        if (childrenCount == 1) {
            node->setValue(node->value() + node->children().front()->value());
            node->setChildren(std::move(node->children().front()->children()));
            compressTrie(node);
        }
        for (auto &child : node->children()) {
            compressTrie(child.get());
        }
    }
    /**
 * @brief looks specified word
 * @param node pointer to current node
 * @param word word to look for
 * @param result resulting string
 */
    static void findWordRecursive(Node *node, std::string word, std::string result, SafeList<std::string> *queue, bool *stop) {
        if (*stop) {
            return;
        }

        if (node == nullptr) {
            std::cerr << "Error: Trie::findWordRecursive: node somewhy empty";
            return;
        }

        if (!node->value().empty())// prevents root node from being add to resulting string(there will be problems outputting it otherwise)
            result += node->value();

        for (auto &chr : node->value()) {
            if (chr == word[0])
                word = word.substr(1, word.size());
        }
        if (node->children().empty() && word.empty()) {// if word was found, and we reached the end of branch
            queue->push_back(result);
        }
        for (auto &childNode : node->children()) {// recursively going through the trie
            findWordRecursive(childNode.get(), word, result, queue, stop);
        }
    }
    template<typename T>
    bool checkIfAsyncTaskFinished(std::future<T> &asyncTask) {
        return asyncTask.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
    }
};


#endif//JB_INTSHIP_2021_COMPRESSEDTRIE_HXX
