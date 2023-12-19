#ifndef AVL_TREE_H
#define AVL_TREE_H

// we define DEBUG in the main function.
// #define DEBUG

/*
AVL map - key : std::string (word), value : std::vector<std::string> (names of files that include word)
Each node will hold a pair -> comparisons will be done with key values
*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <list>
#include <queue>
#include <map>

#include "AvlPair.h"

using namespace std;

/* AvlTree class
 * This implementation is based on the unbalanced binary search tree and adds hight information
 * to the nodes and a balance function to perform the needed rotations.
 */
class AvlTree
{
private:
    struct AvlNode
    {
        AvlPair key;
        AvlNode *left;
        AvlNode *right;
        int height; // AVL tree: keeping track of the height is the difference to a unbalanced binary search tree

        AvlNode(const AvlPair &theKey, AvlNode *lt, AvlNode *rt, int h)
            : key{theKey}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *root;

    static const int ALLOWED_IMBALANCE = 1; // 1 is the default; more will make balancing cheaper
                                            // but the search less efficient.

public:
    /**
     * @brief Default constructor
     */
    AvlTree() : root{nullptr}
    {
    }

    /**
     * @brief Rule-of-3 Part 1: Copy constructor uses internal function clone().
     *
     */
    AvlTree(const AvlTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    /**
     * @brief Rule-of-3 Part 2: Destroy the Binary Search Tree object using the internal
     *   function makeEmpty().
     */
    ~AvlTree()
    {
        makeEmpty();
    }

    /**
     * @brief Rule-of-3 Part 1: Copy constructor uses internal function clone().
     */
    AvlTree &operator=(const AvlTree &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        makeEmpty();
        root = clone(rhs.root);
        return *this;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const std::string &x) const
    {
        return contains(x, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Print the tree structure.
     */
    void prettyPrintTree() const
    {
        prettyPrintTree("", root, false);
    }

    /**
     * Make the tree empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const AvlPair &x)
    {
        insert(x, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(std::string x)
    {
        remove(x, root);
    }

    void printNode(const std::string &x) const
    {
        printNode(x, root);
    }

    void addDocs(const std::string &x, const std::string &y) const
    {
        addDocs(x, y, root);
    }

    int getHeight(AvlNode &t)
    {
        getHeight(t);
    }

    const AvlNode *getRoot() const
    {
        return root;
    }

    bool findDocAt(std::string x, std::string y)
    {
        findDocAt(x, y, root);
    }

    void addToCount(std::string x, std::string y)
    {
        addToCount(x, y, root);
    }

    std::string getDocAt(std::string x, std::string y)
    {
        getDocAt(x, y, root);
    }

    void levelTraversal(std::string path)
    {
        levelTraversal(path, root);
    }

    void store(std::string x, AvlPair &p)
    {
        store(x, p, root);
    }

    bool hasDoc(const std::string &word, const std::string &doc) const
    {
        try
        {
            return findDocAt(word, doc, root);
        }
        catch (const std::out_of_range &)
        {
            return false;
        }
    }

    int getNodeHeight(const std::string &key) const
    {
        const AvlNode *node = findNode(key, root);
        return node ? node->height : -1; // Return -1 if node not found
    }

    std::map<std::string, int> getAllDocs(std::string x)
    {
        getAllDocs(x, root);
    }

#ifdef DEBUG
    /**
     * Check if the tree is balanced and that the height of the nodes is correct.
     * Throws an exception if the tree is not balanced or the height is wrong.
     * This function is not necessary in production code since the tree is always balanced.
     * It is only compiled when DEBUG is defined.
     */

    int check_balance()
    {
        return check_balance(root);
    }
#endif

private:
    std::map<std::string, int> getAllDocs(std::string x, AvlNode *t)
    {
        if (t == nullptr)
            throw std::out_of_range("Node is not in tree.");

        if (x.compare(t->key.getWord()) == 0)
        {
            return t->key.getDocs();
        }
        else if (x.compare(t->key.getWord()) < 0)
            return getAllDocs(x, t->left);
        else
            return getAllDocs(x, t->right);
    }

    void store(std::string x, AvlPair &p, AvlNode *t)
    {
        if (t == nullptr)
            throw std::out_of_range("Node is not in tree.");

        if (x.compare(t->key.getWord()) == 0)
        {
            p.setWord(x);
            std::map<std::string, int> m = t->key.getDocs();
            p.setDocs(m);
        }
        else if (x.compare(t->key.getWord()) < 0)
            store(x, p, t->left);
        else
            store(x, p, t->right);
    }

    std::string getDocAt(std::string x, std::string y, AvlNode *t)
    {
        if (t == nullptr)
            throw std::out_of_range("Node is not in tree.");

        if (x.compare(t->key.getWord()) == 0)
        {
            return t->key.returnDocAt(y);
        }
        else if (x.compare(t->key.getWord()) < 0)
            return getDocAt(x, y, t->left);
        else
            return getDocAt(x, y, t->right);
    }

    void addToCount(std::string x, std::string y, AvlNode *t)
    {
        if (t == nullptr)
            throw std::out_of_range("Node is not in tree.");

        if (x.compare(t->key.getWord()) == 0)
        {
            t->key.plusCountAtLoc(y);
        }
        else if (x.compare(t->key.getWord()) < 0)
            addToCount(x, y, t->left);
        else
            addToCount(x, y, t->right);
    }

    bool findDocAt(std::string x, std::string y, AvlNode *t) const
    {
        if (t == nullptr)
            throw std::out_of_range("Node is not in tree.");

        if (x.compare(t->key.getWord()) == 0)
        {
            return t->key.findDoc(y);
        }
        else if (x.compare(t->key.getWord()) < 0)
        {
            return findDocAt(x, y, t->left);
        }
        else
        {
            return findDocAt(x, y, t->right);
        }
    }

    int getHeight(AvlNode *t)
    {
        if (t == nullptr)
        {
            return 0;
        }
        else
        {
            int leftH = getHeight(t->left);
            int rightH = getHeight(t->right);

            if (leftH > rightH)
            {
                return (leftH + 1);
            }
            else
            {
                return (rightH + 1);
            }
        }
    }

    void levelTraversal(std::string path, AvlNode *t)
    {
        std::ofstream in;
        in.open(path);
        if (in.is_open())
        {
            if (t == nullptr)
            {
                return;
            }
            std::queue<AvlNode *> q;
            q.push(t);
            while (!q.empty())
            {
                AvlNode *curr = q.front();
                in << curr->key.getWord() << std::endl;

                for (auto &it : curr->key.getDocs())
                {
                    in << it.first << "\n";
                }

                in << "-" << std::endl;

                for (auto &it : curr->key.getDocs())
                {
                    in << it.second << " ";
                }

                in << std::endl;

                if (curr->left != nullptr)
                {
                    q.push(curr->left);
                }
                if (curr->right != nullptr)
                {
                    q.push(curr->right);
                }
                q.pop();
            }
            in.close();
        }
    }

    void printNode(const std::string &x, AvlNode *t) const
    {
        if (t == nullptr)
            throw std::out_of_range("Node is not in tree.");

        if (x.compare(t->key.getWord()) == 0)
        {
            std::cout << t->key.getWord() << ": ";
            t->key.printDocs();
            std::cout << std::endl;
        }
        else if (x.compare(t->key.getWord()) < 0)
            return printNode(x, t->left);
        else
            return printNode(x, t->right);
    }

    void addDocs(const std::string &x, const std::string &y, AvlNode *t) const
    {
        if (t == nullptr)
            throw std::out_of_range("Node is not in tree.");

        if (x.compare(t->key.getWord()) == 0)
            t->key.addDoc(y);
        else if (x.compare(t->key.getWord()) < 0)
            return addDocs(x, y, t->left);
        else
            return addDocs(x, y, t->right);
    }

    const AvlNode *findNode(const std::string &key, AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (key == t->key.getWord())
            return t;
        if (key < t->key.getWord())
            return findNode(key, t->left);
        else
            return findNode(key, t->right);
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const AvlPair &x, AvlNode *&t)
    {
        if (t == nullptr)
        {
            t = new AvlNode{x, nullptr, nullptr, 0};
            return; // a single node is always balanced
        }

        if (x < t->key)
            insert(x, t->left);
        else if (t->key < x)
            insert(x, t->right);
        else
        {
        } // Duplicate; do nothing

        // This will call balance on the way back up the tree. It will only balance
        // once at node the where the tree got imbalanced (called node alpha in the textbook)
        // and update the height all the way back up the tree.
        balance(t);
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const std::string &key, AvlNode *&t)
    {
        if (t == nullptr)
        {
            return; // item not found, do nothing
        }

        if (key < t->key.getWord())
        {
            remove(key, t->left);
        }
        else if (key > t->key.getWord())
        {
            remove(key, t->right);
        }
        else if (t->left != nullptr && t->right != nullptr)
        {
            t->key = findMin(t->right)->key;
            remove(t->key.getWord(), t->right);
        }
        else
        {
            AvlNode *oldNode = t;
            if (t->left != nullptr)
            {
                t = t->left;
            }
            else
            {
                t = t->right;
            }
            delete oldNode;
        }

        // update height and balance the tree
        if (t != nullptr)
        {
            t->height = max(height(t->left), height(t->right)) + 1;
            balance(t);
        }
    }

    // finds the node with the minimum key in the subtree rooted at 't'.
    //  returns pointer to node with the minimum key in the subtree.
    AvlNode *findMin(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    /**
     * Internal method to check if x is found in a subtree rooted at t.
     */
    bool contains(const std::string &x, AvlNode *t) const
    {
        if (t == nullptr)
            return false;

        if (x.compare(t->key.getWord()) == 0)
            return true; // Element found.
        else if (x.compare(t->key.getWord()) < 0)
            return contains(x, t->left);
        else
            return contains(x, t->right);
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        return new AvlNode{t->key, clone(t->left), clone(t->right), t->height};
    }

    /**
     * Pretty print the tree structure
     * Uses preorder traversal with R and L swapped (NRL)
     *
     * Modified from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
     */
    void prettyPrintTree(const std::string &prefix, const AvlNode *node, bool isRight) const
    {
        if (node == nullptr)
            return;

        std::cout << prefix;
        // Note: this uses unicode characters for the tree structure. They might not print correctly on
        // all systems (Windows!?!) and all types of output devices.
        std::cout << (isRight ? "├──" : "└──");
        // print the value of the node
        std::cout << node->key << std::endl;

        // enter the next tree level - left and right branch
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true);
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false);
    }

    // Balancing: AVL Rotations

    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    /**
     * 1. Performs rotations if the the the difference of the height stored in t's two child nodes
     *    more than ALLOWED_IMBALANCE.
     * 2. Updates the height information of the note t.
     *
     * Assumes that the high information in the child nodes is correct. This is guaranteed by calling
     * balance() recursively from the inserted node up to the tree node (see insert()). Rotations will
     * only be performed for node alpha (parent of the parent of the inserted node). For all other nodes,
     * only the height will be updated.
     */
    void balance(AvlNode *&t)
    {
        // special case: empty tree
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) // unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t); // case 1 (outside)
            else
                doubleWithLeftChild(t); // case 2 (inside)
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) // unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t); // case 4 (outside)
            else
                doubleWithRightChild(t); // case 3 (inside)
        }
        // else ... no imbalance was created

        // update height
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode *&k2)
    {
#ifdef DEBUG
        cout << "need to rotateWithLeftChild for node " << k2->key << endl;
        cout << "Before:" << endl;
        prettyPrintTree();
#endif

        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
#ifdef DEBUG
        cout << "After:" << endl;
        prettyPrintTree();
#endif
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode *&k1)
    {
#ifdef DEBUG
        cout << "need to rotateWithRightChild for node " << k1->key << endl;
        cout << "Before:" << endl;
        prettyPrintTree();

#endif

        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
#ifdef DEBUG
        cout << "After:" << endl;
        prettyPrintTree();
#endif
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode *&k3)
    {
#ifdef DEBUG
        cout << "doubleWithLeftChild" << endl;
#endif
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode *&k1)
    {
#ifdef DEBUG
        cout << "doubleWithRightChild" << endl;
#endif
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

#ifdef DEBUG
    /**
     * Check if the tree is balanced and that the height of the nodes is correct.
     * Throws an exception if the tree is not balanced or the height is wrong.
     * This function is not necessary in production code since the tree is always balanced.
     * It is only compiled when DEBUG is defined.
     */

    int check_balance(AvlNode *node)
    {
        if (node == nullptr)
        {
            return -1;
        }

        // use LRN traversal to check the balance of the tree
        int lHeight = check_balance(node->left) + 1;
        int rHeight = check_balance(node->right) + 1;

        if (std::abs(lHeight - rHeight) > ALLOWED_IMBALANCE)
        {
            throw std::runtime_error("tree is not balanced in node with key " + std::to_string(node->key) + ".");
        }

        int trueNodeHeight = std::max(lHeight, rHeight);

        if (trueNodeHeight != node->height)
        {
            throw std::runtime_error("node does not have correct height value in node with key " + std::to_string(node->key) + ".");
        }

        return trueNodeHeight;
    }
#endif
};

#endif
