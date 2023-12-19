#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "AvlTree.h"
#include "ParsedDoc.h"
#include "ParsedQuery.h"
#include "AvlPair.h"
#include <map>

#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
using namespace rapidjson;

class IndexHandler
{

private:
    AvlTree persons; // AVL tree for storing person-related data
    AvlTree orgs;    // AVL tree for storing organization-related data
    AvlTree words;   // AVL tree for storing word-related data

    std::ofstream pFile; // file stream for storing person data
    std::ofstream oFile; // file stream for storing organization data
    std::ofstream wFile; // file stream for storing word data

public:
    // method to write the contents of AVL trees to corresponding files
    void write();
    // method to read data from files into AVL trees based on name identifier
    void read(std::string, std::string);
    // method to perform a search based on a parsed query
    void search(ParsedQuery pq);
    // method to print search results based on relevance
    void printSearchResults(std::map<std::string, int> &d);
    // method to reset the index by clearing AVL trees and associated files
    void resetIndex();
    // method to store parsed document data into AVL trees
    void store(ParsedDoc &pd);
    // method to check if all AVL trees are empty
    bool treesEmpty();
    //reset files for updating
    void resetFilesOnly();
};

#endif