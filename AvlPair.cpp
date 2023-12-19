#include "AvlPair.h"

// default constructor, initializes word to an empty string
AvlPair::AvlPair()
{
    word = "";
}

// parameterized constructor, sets the word
AvlPair::AvlPair(std::string word)
{
    this->word = word;
}

// copy constructor
AvlPair::AvlPair(const AvlPair &ap)
{
    this->word = ap.word;
    for (auto &it : ap.docs)
    {
        this->docs.insert({it.first, it.second});
    }
}

// comparison operator for less than
bool AvlPair::operator<(const AvlPair &rhs) const
{
    return word.compare(rhs.word) < 0;
}

// comparison operator for equality
bool AvlPair::operator==(const AvlPair &rhs) const
{
    return word.compare(rhs.word) == 0;
}

// comparison operator for greater than
bool AvlPair::operator>(const AvlPair &rhs) const
{
    return word.compare(rhs.word) > 0;
}

// get the word
std::string AvlPair::getWord()
{
    return word;
}

// get the map of documents and their counts
std::map<std::string, int> AvlPair::getDocs()
{
    return docs;
}

// add a document to the map
void AvlPair::addDoc(std::string doc)
{
    docs.insert({doc, 1});
}

// increment the count for a specific document
void AvlPair::plusCountAtLoc(std::string doc)
{
    std::map<std::string, int>::iterator it = docs.find(doc);
    if (it != docs.end())
    {
        it->second++;
    }
}

// print the documents and their counts
void AvlPair::printDocs()
{
    for (auto it = docs.cbegin(); it != docs.cend(); ++it)
    {
        std::cout << it->first << ":" << it->second << "\n";
    }
}

// check if a document exists in the map
bool AvlPair::findDoc(std::string doc)
{
    return docs.find(doc) != docs.end();
}

// get the document name for a specific document
std::string AvlPair::returnDocAt(std::string doc)
{
    std::map<std::string, int>::iterator it = docs.find(doc);
    if (it != docs.end())
    {
        return it->first;
    }
    return "Doc not found.";
}

// get the count for a specific document
int AvlPair::returnCountAt(std::string doc)
{
    std::map<std::string, int>::iterator it = docs.find(doc);
    if (it != docs.end())
    {
        return it->second;
    }
    return -1;
}

// change the count for a specific document
void AvlPair::changeCount(std::string doc, int count)
{
    std::map<std::string, int>::iterator it = docs.find(doc);
    if (it != docs.end())
    {
        it->second = count;
    }
}

// overloaded << operator for easy printing
std::ostream &operator<<(std::ostream &out, const AvlPair &p)
{
    out << p.word;
    return out;
}

// set the word
void AvlPair::setWord(std::string x)
{
    this->word = x;
}

// set the map of documents and their counts
void AvlPair::setDocs(std::map<std::string, int> &d)
{
    for (auto &it : d)
    {
        this->docs.insert({it.first, it.second});
    }
}
