#include <filesystem>
#include <fstream>
#include <iomanip>
#include <string>

// RapidJSON headers we need for our parsing.
#include "Parser.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

// include ParsedDoc to populate and return ParsedDoc objects
#include "ParsedDoc.h"

using namespace rapidjson;
using namespace std;

ParsedQuery Parser::queryParser(std::string q) {
    // loop until the input string q is empty
    do {
        // find the position of "PERSON:", "ORG:", and "-" in the query string q
        std::size_t pos = q.find("PERSON:");  // position of first char of first match
        std::size_t pos2 = q.find("ORG:");
        std::size_t pos3 = q.find("-");

        if (pos != std::string::npos) {  // if "PERSON:" is found
                                         // extract the person name

            std::size_t start = pos + 7;           // position after "PERSON:"
            std::size_t end = q.find(" ", start);  // Ffnd the end of the person name
            if (end > 1000) {
                end = q.length();  // limit the end position if it's too large
            }

            std::size_t len = end - start;         // calculate the length of the person name
            std::string p = q.substr(start, len);  // extract the person name
            std::string clean = cleanToken(p);
            queryInfo.addPerson(clean);  // add the person name to the ParsedQuery object
            q.erase(start, len);         // erase the extracted word from the query string
            std::size_t len2 = start + 1 - pos;
            q.erase(pos, len2);  // erase PERSON:
        }

        else if (pos2 != std::string::npos) {
            // if "ORG:" is found
            // extract the organization name
            std::size_t start = pos2 + 4;          // position after "ORG:"
            std::size_t end = q.find(" ", start);  // find the end of the organization name
            if (end > 1000) {
                end = q.length();  // limit the end position if it's too large
            }

            std::size_t len = end - start;         // calculate the length of the organization name
            std::string o = q.substr(start, len);  // extract the organization name
            std::string clean = cleanToken(o);
            queryInfo.addOrgs(clean);  // add the org name to the ParsedQuery object
            q.erase(start, len);       // erase org from string
            std::size_t len2 = start + 1 - pos2;
            q.erase(pos2, len2);  // erase ORG:
        }

        else if (pos3 != std::string::npos) {
            // if "-" is found (for negWords)
            // extract the negWord
            std::size_t start = pos3 + 1;          // position after "-"
            std::size_t end = q.find(" ", start);  // find the end of the negWord
            if (end > 1000) {
                end = q.length();  // limit the end position if it's too large
            }

            std::size_t len = end - start;         // calculate the length of the negWord
            std::string n = q.substr(start, len);  // then extract the negWord
            std::string clean = cleanToken(n);
            queryInfo.addNegWords(clean);  // add the negWord to the ParsedQuery object
            q.erase(start, len);           // erase negWord from string
            std::size_t len2 = start + 1 - pos3;
            q.erase(pos3, len2);  // erase "-"
        }

        else {
            // if none of the special tokens are found, consider it as a regular word
            std::size_t len = q.find(" ");  // find the end of the word
            if (len > 1000 || len <= 0) {
                len = q.length();  // limit the end position if it's too large
            }
            std::string n = q.substr(0, len);  // extract the word
            std::string clean = cleanToken(n);
            queryInfo.addWords(clean);  // add the word to the ParsedQuery object
            q.erase(0, len + 1);        // erase the word from string
        }
    } while (!q.empty());  // loop till q (string) is empty

    // return the ParsedQuery object containing the extracted query data
    return queryInfo;
}

std::string Parser::removeNonAlphanumeric(const std::string &str) {
    // regular expression to match non-alphanumeric characters
    const std::regex non_alnum_regex("[^a-zA-Z0-9]");

    // replace non-alphanumeric characters with an empty string
    std::string result = std::regex_replace(str, non_alnum_regex, "");

    return result;
}

std::string Parser::cleanToken(const std::string &token) {
    // gets rid of non alpha numeric characters from each string..
    std::string cleaned = token;

    // remove non-alphanumeric characters from 'cleaned'
    cleaned = removeNonAlphanumeric(cleaned);
    // convert 'cleaned' to lowercase
    for (char &c : cleaned) {
        c = tolower(c);
    }

    return cleaned;
}

void Parser::removeStopWords(std::vector<std::string> &tokens, const std::unordered_set<std::string> &stopWords) {
    // define a lambda function for checking if a word is a stop word
    // returns true if the word is found in the stopWords set
    auto isStopWord = [&stopWords](const std::string &token) {
        return stopWords.find(token) != stopWords.end();
    };

    // use std::remove_if to reorder the elements in the 'tokens' vector,
    // moving the stop words to the end of the vector.
    auto newEnd = std::remove_if(tokens.begin(), tokens.end(), isStopWord);

    // then erase the stop words from the end of the vector.
    tokens.erase(newEnd, tokens.end());
}

std::vector<std::string> Parser::tokenize(const std::string &str, const std::regex re) {
    // https://www.geeksforgeeks.org/tokenizing-a-string-cpp/ for documentation on how to tokenize using regular expressions
    // https://www.informit.com/articles/article.aspx?p=2064649&seqNum=7 further documentation, way more flexible than using strtok for delimeters

    // initialize a regular expression token iterator
    std::sregex_token_iterator it{str.begin(), str.end(), re, -1};
    std::vector<std::string> tokenized;

    // iterate through the tokens and clean each one before adding it to the result vector
    for (auto iter = it; iter != std::sregex_token_iterator(); ++iter) {
        std::string cleanedToken = cleanToken(*iter);

        // add cleaned tokens to the result vector, skipping empty tokens
        if (!cleanedToken.empty()) {
            tokenized.push_back(cleanedToken);
        }
    }

    return tokenized;
}

// used rapidJSONExample provided from class for docParser

ParsedDoc Parser::docParser(const std::string &fileName)  // might want to pass a file instead
{
    // open an ifstream on the file of interest and check that it could be opened.
    ifstream input(fileName);
    if (!input.is_open()) {
        cerr << "cannot open file: " << fileName << endl;
        return ParsedDoc();
    }

    std::cout << "Evaluating File: " << fileName << std::endl;
    std::cout << std::endl;

    // Create a RapidJSON IStreamWrapper using the file input stream above.
    IStreamWrapper isw(input);

    // Create a RapidJSON Document object and use it to parse the IStreamWrapper object above.
    Document d;

    d.ParseStream(isw);

    // Now that the document is parsed, we can access different elements the JSON using
    // familiar subscript notation.

    // This accesses the -title- element in the JSON. Since the value
    //  associated with title is a string (rather than
    //  an array or something else), we call the GetString()
    //  function to return the actual title of the article
    //  as a c-string.

    // add it to ParsedDoc object
    docInfo.addPath(fileName);

    // using regex for tokenizing text
    const std::regex re(R"([\s|,]+)");

    // The Persons entity for which you're building a specific
    //  inverted index is contained in top level -entities- element.
    //  So that's why we subscript with ["entities"]["persons"].
    //  The value associated with entities>persons is an array.
    //  So we call GetArray() to get an iterable collection of elements

    // get document persons

    auto persons = d["entities"]["persons"].GetArray();

    // We iterate over the Array returned from the line above.
    //  Each element kind of operates like a little JSON document
    //  object in that you can use the same subscript notation
    //  to access particular values.

    // iterate over the array of persons
    for (auto &p : persons) {
        std::vector<std::string> tokenizedString = tokenize(p["name"].GetString(), re);
        // for each person, tokenize its name and add cleaned tokens to the ParsedDoc object
        for (auto &t : tokenizedString) {
            std::string cleanedToken = cleanToken(t);
            docInfo.addPerson(cleanedToken);
        }
    }

    // get document organizations
    auto orgs = d["entities"]["organizations"].GetArray();

    // iterate over the array of organizations
    for (auto &o : orgs) {
        std::vector<std::string> tokenizedString = tokenize(o["name"].GetString(), re);
        // for each organization, tokenize its name and add cleaned tokens to the ParsedDoc object
        for (auto &t : tokenizedString) {
            std::string cleanedToken = cleanToken(t);
            docInfo.addOrgs(cleanedToken);
        }
    }

    // get document text
    auto string = d["text"].GetString();

    // puts the tokenized text into a vector of tokens
    // Tokenize the document text and remove stop words
    std::vector<std::string> tokenizedString = tokenize(string, re);
    removeStopWords(tokenizedString, stopWords);

    // goes through vector of words and adds token to the vector of words in ParsedDoc object
    for (auto &t : tokenizedString) {
        std::string cleanedToken = cleanToken(t);
        docInfo.addWords(cleanedToken);
    }

    // now pushed is everything into an object now returning it back as a populated ParsedDoc object

    // close the input file stream
    input.close();

    // return the populated ParsedDoc object
    return docInfo;
}
