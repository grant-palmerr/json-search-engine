#define CATCH_CONFIG_MAIN
#include "AvlPair.h"
#include "AvlTree.h"
#include "catch2/catch.hpp"

TEST_CASE("AvlTree Constructor Tests", "[AvlTree]")
{
    AvlTree myTree;

    SECTION("Tree should be empty after construction")
    {
        REQUIRE(myTree.isEmpty() == true); // make sure tree is empty
    }

    // check to see if empty tree root node is nullptr
    SECTION("Root should be nullptr after construction")
    {
        REQUIRE(myTree.getRoot() == nullptr);
    }

    SECTION("Operations on an empty tree")
    {
        // trying to remove a non-existent element should not crash the tree
        REQUIRE_NOTHROW(myTree.remove("nonexistent"));

        // tree should not contain any element right after construction
        REQUIRE(myTree.contains("anything") == false);
    }
}

TEST_CASE("AvlTree Copy Constructor Tests", "[AvlTree]")
{
    AvlTree originalTree;
    // populate originalTree with AvlPairs
    originalTree.insert(AvlPair("word1"));
    originalTree.insert(AvlPair("word2"));

    AvlTree copiedTree = originalTree;

    SECTION("Test Copy Is Identical to Original")
    {
        REQUIRE(copiedTree.contains("word1") == true);
        REQUIRE(copiedTree.contains("word2") == true);
    }

    SECTION("Test Copy and Original Are Independent")
    {
        copiedTree.insert(AvlPair("newWord"));
        REQUIRE(originalTree.contains("newWord") == false);
    }

    SECTION("Test Copy of an Empty Tree")
    {
        AvlTree emptyTree;
        AvlTree copiedEmptyTree = emptyTree;
        REQUIRE(copiedEmptyTree.isEmpty() == true);
    }
}

TEST_CASE("AvlTree Copy Assignment Operator Tests", "[AvlTree]")
{
    AvlTree originalTree;
    // populate originalTree with AvlPairs
    originalTree.insert(AvlPair("word1"));
    originalTree.insert(AvlPair("word2"));

    AvlTree assignedTree;
    assignedTree = originalTree;

    SECTION("Test Assignment Results in Identical Trees")
    {
        REQUIRE(assignedTree.contains("word1") == true);
        REQUIRE(assignedTree.contains("word2") == true);
    }

    SECTION("Test Self-Assignment Safety")
    {
        originalTree = originalTree;
        // further checks to ensure originalTree remains unchanged
    }

    SECTION("Test Assignment of an Empty Tree")
    {
        AvlTree emptyTree;
        assignedTree = emptyTree;
        REQUIRE(assignedTree.isEmpty() == true);
    }
}

TEST_CASE("AvlTree contains Method", "[AvlTree]")
{
    AvlTree tree;
    tree.insert(AvlPair("word1"));
    tree.insert(AvlPair("word2"));

    SECTION("Contains Existing Elements")
    {
        REQUIRE(tree.contains("word1") == true);
        REQUIRE(tree.contains("word2") == true);
    }

    SECTION("Does Not Contain Non-Existing Elements")
    {
        REQUIRE(tree.contains("word3") == false);
    }

    SECTION("Does Not Contain Empty String")
    {
        REQUIRE(tree.contains("") == false);
    }
}

TEST_CASE("AvlTree isEmpty Method", "[AvlTree]")
{
    AvlTree emptyTree;
    AvlTree nonEmptyTree;
    nonEmptyTree.insert(AvlPair("word"));

    SECTION("Empty Tree")
    {
        REQUIRE(emptyTree.isEmpty() == true);
    }

    SECTION("Non-Empty Tree")
    {
        REQUIRE(nonEmptyTree.isEmpty() == false);
    }

    SECTION("After Making Tree Empty")
    {
        nonEmptyTree.makeEmpty();
        REQUIRE(nonEmptyTree.isEmpty() == true);
    }
}

TEST_CASE("AvlTree makeEmpty Method", "[AvlTree]")
{
    AvlTree tree;
    tree.insert(AvlPair("word1"));
    tree.insert(AvlPair("word2"));
    tree.insert(AvlPair("word3"));

    SECTION("Tree is Not Empty Initially")
    {
        REQUIRE(tree.isEmpty() == false);
    }

    SECTION("Tree is Empty After makeEmpty")
    {
        tree.makeEmpty();
        REQUIRE(tree.isEmpty() == true);
    }

    SECTION("Contains Returns False for All Elements After makeEmpty")
    {
        tree.makeEmpty();
        REQUIRE(tree.contains("word1") == false);
        REQUIRE(tree.contains("word2") == false);
        REQUIRE(tree.contains("word3") == false);
    }
}

TEST_CASE("AvlTree insert Method", "[AvlTree]")
{
    AvlTree tree;

    SECTION("Inserting New Elements")
    {
        tree.insert(AvlPair("word1"));
        REQUIRE(tree.contains("word1") == true);

        tree.insert(AvlPair("word2"));
        REQUIRE(tree.contains("word2") == true);
    }

    SECTION("Inserting Duplicate Elements")
    {
        tree.insert(AvlPair("word1"));
        tree.insert(AvlPair("word1"));
        // inserting a duplicate
        // then checking if tree still behaves correctly
        REQUIRE(tree.contains("word1") == true);
    }

    SECTION("Inserting Multiple Elements")
    {
        tree.insert(AvlPair("word1"));
        tree.insert(AvlPair("word2"));
        tree.insert(AvlPair("word3"));
        REQUIRE(tree.contains("word3") == true);
    }
}

TEST_CASE("AvlTree remove Method", "[AvlTree]")
{
    AvlTree tree;
    tree.insert(AvlPair("word1"));
    tree.insert(AvlPair("word2"));

    SECTION("Removing Existing Element")
    {
        tree.remove("word1");
        REQUIRE(tree.contains("word1") == false);
    }

    SECTION("Removing Non-Existing Element")
    {
        tree.remove("word3");                    // word3 was never inserted
        REQUIRE(tree.contains("word2") == true); // check if other elements are unaffected
    }

    SECTION("Removing All Elements")
    {
        tree.remove("word1");
        tree.remove("word2");
        REQUIRE(tree.isEmpty() == true);
    }
}

TEST_CASE("AvlTree addDocs Method", "[AvlTree]")
{
    AvlTree tree;
    tree.insert(AvlPair("word1"));

    SECTION("Adding Docs to Existing Node")
    {
        tree.addDocs("word1", "doc1");
        // validate through a method that can check the added document
        REQUIRE(tree.hasDoc("word1", "doc1") == true);
    }

    SECTION("Adding Multiple Docs to a Node")
    {
        tree.addDocs("word1", "doc1");
        tree.addDocs("word1", "doc2");
        // validate both docs are added
        REQUIRE(tree.hasDoc("word1", "doc2") == true);
    }
}

TEST_CASE("AvlTree getRoot Method", "[AvlTree]")
{
    AvlTree tree;

    SECTION("Root is nullptr in an Empty Tree")
    {
        REQUIRE(tree.getRoot() == nullptr);
    }

    SECTION("Root is Not nullptr After Insertion")
    {
        tree.insert(AvlPair("word1"));
        REQUIRE(tree.getRoot() != nullptr);
    }
}

TEST_CASE("AvlTree Node Heights", "[AvlTree]")
{
    AvlTree tree;

    SECTION("Predicted Heights After Insertions")
    {
        tree.insert(AvlPair("word3"));
        tree.insert(AvlPair("word1"));
        tree.insert(AvlPair("word4"));
        tree.insert(AvlPair("word2"));

        // heights are predicted based on the expected balance of the AVL tree
        REQUIRE(tree.getNodeHeight("word3") == 2);
        REQUIRE(tree.getNodeHeight("word1") == 1);
        REQUIRE(tree.getNodeHeight("word4") == 0);
        REQUIRE(tree.getNodeHeight("word2") == 0);
    }

    SECTION("Predicted Heights After Removals")
    {
        tree.insert(AvlPair("word3"));
        tree.insert(AvlPair("word1"));
        tree.insert(AvlPair("word4"));
        tree.remove("word1");

        // Heights after removal
        REQUIRE(tree.getNodeHeight("word3") == 1);
        REQUIRE(tree.getNodeHeight("word4") == 0);
    }
}

TEST_CASE("AvlTree hasDoc Method", "[AvlTree]")
{
    AvlTree tree;
    tree.insert(AvlPair("word1"));
    tree.addDocs("word1", "doc1");
    tree.addDocs("word1", "doc2");

    SECTION("Document Exists for a Word")
    {
        REQUIRE(tree.hasDoc("word1", "doc1") == true);
    }

    SECTION("Document Does Not Exist for a Word")
    {
        REQUIRE(tree.hasDoc("word1", "doc3") == false);
    }

    SECTION("Word Does Not Exist in the Tree")
    {
        REQUIRE(tree.hasDoc("word2", "doc1") == false);
    }
}

TEST_CASE("AvlTree getNodeHeight Method", "[AvlTree]")
{
    AvlTree tree;
    tree.insert(AvlPair("word1")); // this makes a balanced tree
    tree.insert(AvlPair("word2"));
    tree.insert(AvlPair("word3"));

    SECTION("Height of Existing Node")
    {
        // knowing the tree structure after insertions
        REQUIRE(tree.getNodeHeight("word1") >= 0);
    }

    SECTION("Height of Non-Existing Node")
    {
        REQUIRE(tree.getNodeHeight("word4") == -1);
    }
}
