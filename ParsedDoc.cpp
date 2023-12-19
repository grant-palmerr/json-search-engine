#include "ParsedDoc.h"

#include <iomanip>

ParsedDoc::ParsedDoc() {
    // initalize all the members for PasedDoc to empty/default values
    persons = {};
    orgs = {};
    words = {};
    path = "";
}

// getter function that returns the persons vector
std::vector<std::string> ParsedDoc::getPersons() {
    return persons;
}

// getter function that returns the orgs vector
std::vector<std::string> ParsedDoc::getOrgs() {
    //
    return orgs;
}

// getter function that returns the words vector
std::vector<std::string> ParsedDoc::getWords() {
    //
    return words;
}

// getter function that returns the path of the file
std::string ParsedDoc::getPath() {
    return path;
}

// adds a person (given as a string s) to the person vector
void ParsedDoc::addPerson(std::string s) {
    persons.push_back(s);
}

// adds a org (given as a string s) to the org vector
void ParsedDoc::addOrgs(std::string s) {
    orgs.push_back(s);
}

// adds path (given as a string s) to the path member
void ParsedDoc::addPath(std::string s) {
    path = s;
}

// adds a word (given as a string s) to the words vector
void ParsedDoc::addWords(std::string s) {
    words.push_back(s);
}

// prints all the elements in the persons vector to the output for testing
void ParsedDoc::printPersons() {
    std::cout << "Document Person(s): " << std::endl;
    for (size_t i = 0; i < persons.size(); i++) {
        std::cout << "    > " << std::setw(30) << std::left << persons[i] << std::endl;
    }
    std::cout << std::endl;
}

// print the path to output for testing
void ParsedDoc::printPath() {
    std::cout << "Document Path: ";
    std::cout << path << std::endl;

    std::cout << std::endl;
}

// prints all the elements in the orgs vector to the output for testing
void ParsedDoc::printOrgs() {
    std::cout << "Document Organization(s): " << std::endl;

    for (size_t i = 0; i < orgs.size(); i++) {
        std::cout << "    > " << std::setw(30) << std::left << orgs[i] << std::endl;
    }
    std::cout << std::endl;
}

// prints all the elements in the words vector to the output for testing
void ParsedDoc::printWords() {
    std::cout << "Document Word(s): " << std::endl;

    for (size_t i = 0; i < words.size(); i++) {
        std::cout << "    > " << std::setw(30) << std::left << words[i] << std::endl;
    }

    std::cout << std::endl;
}

void ParsedDoc::convertPandInsert(AvlTree &t) {
    // iterate through the persons vector
    for (std::size_t i = 0; i < persons.size(); i++) {
        // check if the AVL tree t contains the person already
        if (t.contains(persons[i])) {
            // if the person is found in the tree, check if the document is already associated with the person
            if (t.findDocAt(persons[i], getPath())) {
                // if the document is already associated, increment the document count for the person
                t.addToCount(persons[i], getPath());
            } else {
                // if the document is not associated, add the document to the person's list of documents
                t.addDocs(persons[i], getPath());
            }
        } else {
            // if the person is not found in the tree, create a new AvlPair and add the document to it
            AvlPair ap(persons[i]);
            ap.addDoc(getPath());
            t.insert(ap);
        }
    }
}

void ParsedDoc::convertOandInsert(AvlTree &t) {
    // iterate through the orgs vector
    for (std::size_t i = 0; i < orgs.size(); i++) {
        // check if the AVL tree t contains the org already
        if (t.contains(orgs[i])) {
            // if the org is found in the tree, check if the document is already associated with the org
            if (t.findDocAt(orgs[i], getPath())) {
                // if the document is already associated, increment the document count for the org
                t.addToCount(orgs[i], getPath());
            } else {
                // if the document is not associated, add the document to the orgs's list of documents
                t.addDocs(orgs[i], getPath());
            }
        } else {
            // if the org is not found in the tree, create a new AvlPair and add the document to it
            AvlPair ap(orgs[i]);
            ap.addDoc(getPath());
            t.insert(ap);
        }
    }
}

void ParsedDoc::convertWandInsert(AvlTree &t) {
    // iterate through the words vector
    for (std::size_t i = 0; i < words.size(); i++) {
        // check if the AVL tree t contains the word already
        if (t.contains(words[i])) {
            // if the word is found in the tree, check if the document is already associated with the word
            if (t.findDocAt(words[i], getPath())) {
                // if the document is already associated, increment the document count for the word
                t.addToCount(words[i], getPath());
            } else {
                // if the document is not associated, add the document to the word's list of documents
                t.addDocs(words[i], getPath());
            }
        } else {
            // if the word is not found in the tree, create a new AvlPair and add the document to it
            AvlPair ap(words[i]);
            ap.addDoc(getPath());
            t.insert(ap);
        }
    }
}
