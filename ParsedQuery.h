#ifndef PARSEDQUERY_H
#define PARSEDQUERY_H

#include <iostream>
#include <vector>

class ParsedQuery {
   private:
    // vectors to hold the extracted data from a query for indexing later on

    std::vector<std::string> persons;
    std::vector<std::string> orgs;
    std::vector<std::string> words;
    std::vector<std::string> negWords;

   public:
    // ParsedQuery default constructor
    ParsedQuery();

    // getters for vectors
    std::vector<std::string> getPersons();
    std::vector<std::string> getOrgs();
    std::vector<std::string> getWords();
    std::vector<std::string> getNegWords();

    // object setters
    void addPerson(std::string s);
    void addOrgs(std::string s);
    void addWords(std::string s);
    void addNegWords(std::string s);

    // prints for testing
    void printPersons();
    void printOrgs();
    void printNegWords();
    void printWords();

    // gets a person at desired index (int) in persons vector
    std::string returnPersonsAt(int);
};

#endif