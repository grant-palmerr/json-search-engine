#ifndef PARSEDDOC_H
#define PARSEDDOC_H

#include <iostream>
#include <vector>

#include "AvlTree.h"

class ParsedDoc {
   private:
    // vectors to hold the extracted data from a document for indexing later on
    std::vector<std::string> persons;
    std::vector<std::string> orgs;
    std::vector<std::string> words;
    std::string path;

   public:
    // default constructor
    ParsedDoc();

    // object getters
    std::vector<std::string> getPersons();
    std::vector<std::string> getOrgs();
    std::vector<std::string> getWords();
    std::string getPath();

    // object setters
    void addPerson(std::string s);
    void addOrgs(std::string s);
    void addWords(std::string s);
    void addPath(std::string s);

    // prints for testing
    void printPersons();
    void printOrgs();
    void printWords();
    void printPath();

    // functions to convert and insert data into an AVLTree
    void convertPandInsert(AvlTree &t);
    void convertOandInsert(AvlTree &t);
    void convertWandInsert(AvlTree &t);
};

#endif