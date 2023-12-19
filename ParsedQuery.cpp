#include "ParsedQuery.h"

ParsedQuery::ParsedQuery() {
    // initalize all the vectors for extracted query data to empty

    persons = {};
    orgs = {};
    words = {};
    negWords = {};
}

// return a person at a specific index in the persons vector
std::string ParsedQuery::returnPersonsAt(int index) {
    if (index >= 0 && index < persons.size()) {
        return persons[index];
    } else {
        return "Index out of bounds";
    }
}

// getter function that returns the persons vector
std::vector<std::string> ParsedQuery::getPersons() {
    return persons;
}

// getter function that returns the orgs vector
std::vector<std::string> ParsedQuery::getOrgs() {
    return orgs;
}

// getter function that returns the words vector
std::vector<std::string> ParsedQuery::getWords() {
    return words;
}

// getter function that returns the negWords vector
std::vector<std::string> ParsedQuery::getNegWords() {
    return negWords;
}

// adds a person (given as a string s) to the person vector
void ParsedQuery::addPerson(std::string s) {
    persons.push_back(s);
}

// adds a org (given as a string s) to the orgs vector
void ParsedQuery::addOrgs(std::string s) {
    orgs.push_back(s);
}

// adds a word (given as a string s) to the words vector
void ParsedQuery::addWords(std::string s) {
    words.push_back(s);
}

// adds a negWord (given as a string s) to the negWords vector
void ParsedQuery::addNegWords(std::string s) {
    negWords.push_back(s);
}

// prints all the elements in the persons vector to the output for testing
void ParsedQuery::printPersons() {
    for (int i = 0; i < persons.size(); i++) {
        std::cout << persons[i] << " ";
    }
    std::cout << std::endl;
}

// prints all the elements in the orgs vector to the output for testing
void ParsedQuery::printOrgs() {
    for (int i = 0; i < orgs.size(); i++) {
        std::cout << orgs[i] << " ";
    }
    std::cout << std::endl;
}

// prints all the elements in the negWords vector to the output for testing
void ParsedQuery::printNegWords() {
    for (int i = 0; i < negWords.size(); i++) {
        std::cout << negWords[i] << " ";
    }
    std::cout << std::endl;
}

// prints all the elements in the words vector to the output for testing
void ParsedQuery::printWords() {
    for (int i = 0; i < words.size(); i++) {
        std::cout << words[i] << " ";
    }
    std::cout << std::endl;
}
