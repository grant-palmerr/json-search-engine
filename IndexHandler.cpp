#include "IndexHandler.h"

// check if all AVL trees are empty
bool IndexHandler::treesEmpty() {
    // must meel all conditions, if all three AVL trees (persons, words, orgs) are empty
    if (persons.isEmpty() && words.isEmpty() && orgs.isEmpty()) {
        return true;
    }
    // if not
    return false;
}

// reset index files (clearing contents)
void IndexHandler::resetFilesOnly() {
    std::ofstream ofs;  // clearing files

    // clear the contents of the orgs.txt file
    ofs.open("/users7/cse/ageer/DataStrc/assignment-4-search-engine-gitoutofhere-1/avl_trees/orgs.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    // clear the contents of the persons.txt file
    ofs.open("/users7/cse/ageer/DataStrc/assignment-4-search-engine-gitoutofhere-1/avl_trees/persons.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    // clear the contents of the words.txt file
    ofs.open("/users7/cse/ageer/DataStrc/assignment-4-search-engine-gitoutofhere-1/avl_trees/words.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

// write data from AVL trees to corresponding files
void IndexHandler::write()  // store current avl trees in appropriate files
{
    // write the data from the persons AVL tree to the persons.txt file
    persons.levelTraversal("../avl_trees/persons.txt");
    // write the data from the orgs AVL tree to the persons.txt file
    orgs.levelTraversal("../avl_trees/orgs.txt");
    // write the data from the persons AVL tree to the words.txt file
    words.levelTraversal("../avl_trees/words.txt");
}

// read data from files and populate AVL trees
void IndexHandler::read(std::string path, std::string name) {
    // clear the corresponding AVL tree based on the 'name' parameter
    if (name.compare("p") == 0) {
        persons.makeEmpty();  // clear the AVL tree for persons
    } else if (name.compare("o") == 0) {
        orgs.makeEmpty();  // clear the AVL tree for orgs
    } else {
        words.makeEmpty();  // clear the AVL tree for words
    }

    std::string word;
    std::string doc;
    int num;

    // open and parse the specified file
    // parse files: restore words, docs, and counts -> test for persons
    std::ifstream Tree;
    Tree.open(path);
    if (Tree.is_open()) {
        // read word and document pairs from the file
        while (Tree >> word) {
            int count = 0;
            AvlPair ap(word);
            Tree >> doc;

            // read document names until a '-' is encountered, signifying the end of document names for the current word
            do {
                ap.addDoc(doc);
                count++;
                Tree >> doc;
            } while (doc.compare("-") != 0);

            // read and assign document counts for the current word
            for (int i = 0; i < count; i++) {
                Tree >> num;
                ap.changeCount(word, num);
            }

            // insert the AvlPair into the corresponding AVL tree based on 'name'
            if (name.compare("p") == 0) {
                persons.insert(ap);  // insert into the AVL tree for persons
            } else if (name.compare("o") == 0) {
                orgs.insert(ap);  // insert into the AVL tree for orgs
            } else {
                words.insert(ap);  // insert into the AVL tree for words
            }
        }
        Tree.close();
    } else {
        std::cout << "Could not open file.";  // handle the case where the file cannot be opened
    }
}

// perform a search using a ParsedQuery object
void IndexHandler::search(ParsedQuery pq) {
    std::map<std::string, int> d;  // create a map to store document paths and their scores

    // loop through the persons in the ParsedQuery
    for (std::size_t i = 0; i < pq.getPersons().size(); i++) {
        std::string s = pq.getPersons()[i];
        AvlPair p;
        persons.store(s, p);
        // check if the persons AVL tree contains the person
        if (persons.contains(s)) {
            for (auto &it : p.getDocs())  // store doc files in new map
            {
                // store document files in the 'd' map
                d.insert({it.first, it.second});
            }
        }
    }

    // loop through the orgs in the ParsedQuery
    for (std::size_t i = 0; i < pq.getOrgs().size(); i++)  // loop through pq orgs
    {
        std::string s = pq.getOrgs()[i];
        // check if the orgs AVL tree contains the organization
        if (orgs.contains(s)) {
            AvlPair p;  // find that node in avl tree persons
            orgs.store(s, p);

            for (auto &it : p.getDocs())  // loop through docs map
            {
                if (d.find(it.first) != d.end()) {  // if map already has doc, add counts together
                    d.find(it.first)->second += it.second;
                } else {  // if it doesnt, store file in map
                    d.insert(it);
                }
            }
        }
    }

    for (std::size_t i = 0; i < pq.getWords().size(); i++)  // loop through pq orgs
    {
        std::string s = pq.getWords()[i];
        if (words.contains(s)) {
            AvlPair p;  // find that node in avl tree persons
            words.store(s, p);

            for (auto &it : p.getDocs())  // loop through docs map
            {
                if (d.find(it.first) != d.end()) {  // if map already has doc, add counts together
                    d.find(it.first)->second += it.second;
                } else {  // if it doesnt, store file in map
                    d.insert(it);
                }
            }
        }
    }

    for (std::size_t i = 0; i < pq.getNegWords().size(); i++)  // loop through neg words
    {
        std::string s = pq.getNegWords()[i];
        if (words.contains(s)) {  // check if in words avl tree
            AvlPair p;            // find that node in avl tree persons
            words.store(s, p);
            for (auto &it : p.getDocs())  // loop through docs map
            {
                if (d.find(it.first) != d.end()) {  // if you can find the doc in d map...
                    d.erase(it.first);              // remove from eligible docs
                }
            }
        }
    }

    // print search results
    printSearchResults(d);
}

// print search results with document details
void IndexHandler::printSearchResults(std::map<std::string, int> &d) {
    std::map<std::string, int> paths;  // store document paths with their corresponding counts
    int count = 1;                     // initialize count for ranking documents

    while (d.size() > 0) {  // do till count = 0 || d is empty

        // find key with highest count ->
        if (d.size() == 0 || count > 15) {  // exit loop if the document map is empty or the count exceeds 15 (precaution)
            break;
        }
        auto pr = std::max_element(d.begin(), d.end(), [](const auto &x, const auto &y) { return x.second < y.second; });
        paths.insert({pr->first, count});  // store the document path in the 'paths' map along with its rank
        d.erase(pr->first);                // remove the document from the original map
        count++;
    };

    std::string ans = "";  // initialize a variable to store user's input for continuing

    do {
        // loop through ranks (1 to 15) to display document titles, publication info, and date
        std::cout << std::endl;
        for (int i = 1; i < 16; i++) {  // print titles, publication, and date of publication ->
            // find doc with count == i ->
            for (auto it : paths) {
                if (it.second == i) {  // once found... print
                    ifstream input(it.first);
                    if (!input.is_open())  // check if we can open file
                    {
                        std::cerr << "cannot open file: " << it.first << std::endl;
                    } else {
                        // Parse the JSON document and display its title, publisher (if available), and publication date
                        // print titles, publication, and date of publication
                        IStreamWrapper isw(input);
                        Document d;
                        d.ParseStream(isw);
                        // extract info if it exists for printing results
                        if (d.HasMember("publisher")) {
                            std::cout << it.second << ". " << d["title"].GetString() << " : " << d["publisher"].GetString() << " - " << d["published"].GetString() << "\n";
                        } else {
                            std::cout << it.second << ". " << d["title"].GetString() << " - " << d["published"].GetString() << "\n";
                        }

                        std::cout << std::endl;
                    }
                    input.close();
                    break;  // break from loop after printing document
                }
            }
        }

        int num = 0;
        std::cout << "Select an article to open (enter number): ";
        std::cin >> num;
        std::cout << std::endl;

        // open and display the selected document's text content
        for (auto it : paths) {
            if (it.second == num) {
                ifstream input(it.first);
                if (!input.is_open())  // check if we can open file
                {
                    std::cerr << "cannot open file: " << it.first << std::endl;
                } else {  // print text
                          // Parse the JSON document and print its text content
                    IStreamWrapper isw(input);
                    Document d;
                    d.ParseStream(isw);
                    std::cout << d["text"].GetString();
                }
                input.close();
                break;  // break from loop
            }
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Go back and open another? (yes or no) : ";  // Prompt the user to continue or exit the loop
        cin >> ans;
    } while (ans.compare("yes") == 0 || ans.compare("Yes") == 0);
}

// reset the index by clearing AVL trees and associated files
void IndexHandler::resetIndex() {
    // clear AVL trees
    persons.makeEmpty();
    orgs.makeEmpty();
    words.makeEmpty();

    std::ofstream ofs;  // clearing files

    // clear the organizations AVL tree file
    ofs.open("/users7/cse/ageer/DataStrc/assignment-4-search-engine-gitoutofhere-1/avl_trees/orgs.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    // clear the persons AVL tree file
    ofs.open("/users7/cse/ageer/DataStrc/assignment-4-search-engine-gitoutofhere-1/avl_trees/persons.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    // clear the words AVL tree file
    ofs.open("/users7/cse/ageer/DataStrc/assignment-4-search-engine-gitoutofhere-1/avl_trees/words.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

// store parsed document information into the respective AVL trees
void IndexHandler::store(ParsedDoc &pd) {
    // convert and insert organization information into the organizations AVL tree
    pd.convertOandInsert(orgs);

    // convert and insert person information into the persons AVL tree
    pd.convertPandInsert(persons);

    // convert and insert word information into the words AVL tree
    pd.convertWandInsert(words);
}
