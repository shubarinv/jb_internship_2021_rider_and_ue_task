//
// Created by vhundef on 02.04.2021.
//

#include "Trie.hxx"
int main(){
    Trie trie;
    trie.readFromFile("../../src/words.txt");
    trie.findRecursive("test");
    return 0;
}

