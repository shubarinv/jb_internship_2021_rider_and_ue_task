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
    Trie(){
        root=new Node();
    }
    explicit Trie(std::string filename){
        root=new Node();
    }

    // functions
    void addWord(std::string word){
        throw std::logic_error("Not implemented");
    }
    void findWord(std::string word){
        throw std::logic_error("Not implemented");
    }
    bool hasWord(std::string word){
        throw std::logic_error("Not implemented");
    }

private:
    Node* root{nullptr};
};


#endif//JB_INTSHIP_2021_TRIE_HXX
