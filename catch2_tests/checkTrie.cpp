//
// Created by vhund on 03.04.2021.
//

#include "Trie.hxx"
#include "catch.hpp"

TEST_CASE("Checking Trie", "[Trie]") {
    SECTION("AddWord") {
        SECTION("Calling addWord() directly") {
            Trie trie;
            trie.addWord("test");
            REQUIRE(trie.getRoot()->getChild('t')->getChild('e')->getChild('s')->getChild('t') != nullptr);
        }
        SECTION("Using readFromFile()") {
            SECTION("reading empty file") {
                Trie trie;
                trie.readFromFile("../../catch2_tests/emptyFile.txt");
                REQUIRE(trie.getRoot()->children().empty());
            }
            SECTION("reading file with content") {
                Trie trie;
                trie.readFromFile("../../catch2_tests/fileWithContent.txt");
                REQUIRE(!trie.getRoot()->children().empty());
            }
        }
    }
    SECTION("Find word"){
        Trie trie;
        trie.readFromFile("../../catch2_tests/fileWithContent.txt");
        REQUIRE(trie.hasWord("JetBrains"));
        REQUIRE(trie.hasWord("Is the best"));
        REQUIRE(trie.hasWord("SpaceX"));
        REQUIRE(trie.hasWord("Wenhop"));
        REQUIRE(trie.hasWord("SN15"));
        REQUIRE(trie.hasWord("Test"));
        REQUIRE_FALSE(trie.hasWord("test"));
        REQUIRE(trie.hasWord("tesla"));
        REQUIRE_FALSE(trie.hasWord("Tesla"));
    }
}