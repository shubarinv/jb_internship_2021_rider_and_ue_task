//
// Created by vhund on 03.04.2021.
//

#include "Trie.hxx"
#include "catch.hpp"

TEST_CASE("Checking Trie", "[Trie]") {
    SECTION("AddWord") {
        SECTION("Calling addWord() directly") {
            CompressedTrie trie;
            trie.addWord("test");
            REQUIRE(trie.hasWord("test"));
        }
        SECTION("Using readFromFile()") {
            SECTION("reading empty file") {
                CompressedTrie trie;
                trie.readFromFile("../../catch2_tests/emptyFile.txt");
                REQUIRE(trie.getRoot()->children().empty());
            }
            SECTION("reading file with content") {
                CompressedTrie trie;
                trie.readFromFile("../../catch2_tests/fileWithContent.txt");
                REQUIRE(!trie.getRoot()->children().empty());
            }
        }
    }
    SECTION("Find word") {
        CompressedTrie trie;
        SafeQueue<std::string>results;
        trie.readFromFile("../../catch2_tests/fileWithContent.txt");
        REQUIRE(trie.hasWord("JetBrains"));
        REQUIRE(trie.hasWord("Is the best"));
        REQUIRE(trie.hasWord("SpaceX"));
        REQUIRE(trie.hasWord("Wenhop"));
        REQUIRE(trie.hasWord("SN15"));
        REQUIRE(trie.hasWord("Test"));
        REQUIRE(trie.hasWord("tesla"));
        trie.findRecursive("et",&results);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
        while (!results.empty()){
            std::cout<<results.dequeue()<<std::endl;
        }
    }
}