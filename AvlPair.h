#ifndef AVLPAIR_H
#define AVLPAIR_H

#include <iostream>
#include <vector>
#include <fstream>
#include <map>

class AvlPair
{

private:
    std::string word;           // the word associated with this AvlPair
    std::map<std::string, int> docs; // a map storing document names and their corresponding counts

public:
    AvlPair();                 // default constructor, initializes word to an empty string
    AvlPair(std::string word); // parameterized constructor, sets the word
    AvlPair(const AvlPair &ap); // copy constructor

    // nessecary comparison operators
    bool operator<(const AvlPair &rhs) const;
    bool operator==(const AvlPair &rhs) const;
    bool operator>(const AvlPair &rhs) const;

    friend std::ostream &operator<<(std::ostream &out, const AvlPair &p);

    std::string getWord();                        // get the word
    std::map<std::string, int> getDocs();         // get the map of documents and their counts
    void addDoc(std::string doc);                 // add a document to the map
    void plusCountAtLoc(std::string doc);         // increment the count for a specific document
    void printDocs();                             // print the documents and their counts
    bool findDoc(std::string doc);                // check if a document exists in the map
    std::string returnDocAt(std::string doc);     // get the document name for a specific document
    int returnCountAt(std::string doc);           // get the count for a specific document
    void changeCount(std::string doc, int count); // change the count for a specific document
    void setWord(std::string word);               // det the word
    void setDocs(std::map<std::string, int> &d);  // set the map of documents and their counts
};

#endif
