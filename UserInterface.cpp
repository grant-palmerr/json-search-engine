#include "UserInterface.h"

#include <chrono>
#include <filesystem>

// UIDisplay()
// calls a function that Displays a menu with three options that the user can interact with:
/* Option 1: If the user wants a directory of files indexed…
Allow for creation of their own index of a directory containing files to be indexed (Stored in PROBABLY A CSV FILE)
Calls index function
Option 2: If the user wants to read/write to an index…
Calls PersistIndex function
Option 3: If the user wants to search one or multiple queries…
Allow user to enter a query(s) */
// calls query function within a for loop (to allow for multiple query calls)
// calls a result render function to display the current search results of that query */

UserInterface::UserInterface() {
    count = 0;
}
int UserInterface::UIDisplay() {
    // initialize user choice
    int choice;

    // use a do-while loop to repeatedly display the menu until a valid choice is made
    do {
        std::cout << "==============================================" << std::endl;
        std::cout << "               ~Search Engine~                " << std::endl;
        std::cout << "----------------------------------------------" << std::endl;
        std::cout << "1. Create or Update Index" << std::endl;
        std::cout << "2. Read/Write to Index" << std::endl;
        std::cout << "3. Search Queries" << std::endl;
        std::cout << "4. Exit Program" << std::endl;  // exit option
        std::cout << "==============================================" << std::endl;
        std::cout << "Select an option (1 | 2 | 3 | 4): ";

        std::cin >> choice;
        std::cout << std::endl;

    } while (!(choice == 1 || choice == 2 || choice == 3 || choice == 4));  // must have one of these to continue

    return choice;
}

// DisplayChoice()
// takes the User to the Create/Update Index SUB-Section of the UI Menu for Creating/Updating an Index, to separate functionality and make the menu more dynamic
void UserInterface::DisplayChoice(const int x) {
    // if user chooses 1 ....
    if (x == 1) {
        // initialize user choice
        int choice;

        // use a do-while loop to repeatedly display the menu until a valid choice is made
        do {
            std::cout << "====================================================" << std::endl;
            std::cout << "||              Create or Update Index           || " << std::endl;
            std::cout << "====================================================" << std::endl;
            std::cout << "Transforms a simple directory full of documents into " << std::endl;
            std::cout << "an efficient, searchable index. Choose an option:" << std::endl;

            std::cout << "----------------------------------------------------" << std::endl;
            std::cout << "1. Update Index: " << std::endl;
            std::cout << "     - Refresh an existing index with the latest info " << std::endl;
            std::cout << "       from a directory. Ideal for after adding or modifying " << std::endl;
            std::cout << "       files in a directory" << std::endl;
            std::cout << "----------------------------------------------------" << std::endl;
            std::cout << "2. Create Index: " << std::endl;
            std::cout << "     - Go through a specified directory and create a new   " << std::endl;
            std::cout << "       index of all contained documents. For accessing files   " << std::endl;
            std::cout << "       quickly and accurately with search queries." << std::endl;
            std::cout << "3. Return to Main Menu" << std::endl;
            std::cout << "====================================================" << std::endl;
            std::cout << "Select an option (1 | 2 | 3): ";

            std::cin >> choice;
            std::cout << std::endl;

        } while (!(choice == 1 || choice == 2 || choice == 3));  // must have one of these to continue

        // depending on choice do..
        if (choice == 1) {
            // call the UpdateIndex() function to refresh an existing index with the latest information from a directory takes to subsection where it prompts user to enter directory path they want to updated
            UpdateIndex();
        } else if (choice == 2) {
            // call the CreateIndex() function to go through a specified directory and create a new index of all contained documents. Takes to subsection where it prompts user to enter directory path they want to created
            // here
            auto start = std::chrono::high_resolution_clock::now();
            CreateIndex();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Create Index for small_data set Executation time: " << duration << " ms" << std::endl;
        } else if (choice == 3) {
            // exit subsection back to original menu
            return;
        }
    }

    // if user choose 2....

    else if (x == 2) {
        // initialize user choice
        int choice;

        // use a do-while loop to repeatedly display the menu until a valid choice is made
        do {
            std::cout << "====================================================" << std::endl;
            std::cout << "||              Read or Write an Index            || " << std::endl;
            std::cout << "====================================================" << std::endl;
            std::cout << "Transforms a simple directory full of documents into " << std::endl;
            std::cout << "an efficient, searchable index. Choose an option:" << std::endl;

            std::cout << "----------------------------------------------------" << std::endl;
            std::cout << "1. Read an Index from a File: " << std::endl;
            std::cout << "     - Offers straightforward, fast access to your organized data, " << std::endl;
            std::cout << "       ideal for when you need to quickly find and utilize specific" << std::endl;
            std::cout << "       information within your collection of documents. " << std::endl;
            std::cout << "----------------------------------------------------" << std::endl;
            std::cout << "2. Write an Index to a File: " << std::endl;
            std::cout << "     - Ideal for when you need to save that have been organized in " << std::endl;
            std::cout << "       your index. This means previous indexing efforts are preserved. " << std::endl;
            std::cout << "       the next time the application runs, it can reload the index from " << std::endl;
            std::cout << "       the file instead of having to recreate it from scratch. " << std::endl;
            std::cout << "3. Return to Main Menu" << std::endl;
            std::cout << "====================================================" << std::endl;
            std::cout << "Select an option (1 | 2 | 3): ";

            std::cin >> choice;
            std::cout << std::endl;

        } while (!(choice == 1 || choice == 2 || choice == 3));  // must have one of these to continue

        if (choice == 1) {
            // call the index handler to read an index from a file

            ih.read("../avl_trees/persons.txt", "p");
            ih.read("../avl_trees/orgs.txt", "o");
            ih.read("../avl_trees/words.txt", "w");

        } else if (choice == 2) {
            // call the index handler to write an index to a file

            ih.write();

        } else {
            // exit subsection back to original menu
            return;
        }
    }
    // else user choosed 3 so ....
    else {
        // initialize a string to store the user's query
        std::string query;
        // load data from index files for persons, organizations, and words

        // prompt the user to enter a search query

        std::cout << "ENTER QUERY: ";
        std::cin.ignore();
        std::getline(std::cin, query);

        ih.read("../avl_trees/persons.txt", "p");
        ih.read("../avl_trees/orgs.txt", "o");
        ih.read("../avl_trees/words.txt", "w");

        // then initialize a Parser object to parse the user's query
        Parser parser;
        ParsedQuery p;

        // parse the user's query using the queryParser() function
        p = parser.queryParser(query);

        ih.search(p);
    }
}

void UserInterface::UpdateIndex() {
    std::string directoryPath;  // the directory to index

    // get the path from user, does rely on user to be correct and enter correct path
    std::cout << "Enter directory path to be indexed: ";
    cin >> directoryPath;
    std::cout << std::endl;

    // iterate through the directory and its subdirectories
    auto it = filesystem::recursive_directory_iterator(directoryPath);
    for (const auto &entry : it) {
        // check if the entry is a regular file with a .json extension
        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            // inintialize objects to perform parsing and indexing
            Parser p;
            ParsedDoc pd;

            // take current files, read in data and store data in trees
            ih.read("../avl_trees/persons.txt", "p");
            ih.read("../avl_trees/orgs.txt", "o");
            ih.read("../avl_trees/words.txt", "w");

            // empty files
            ih.resetFilesOnly();

            // parse the JSON file and store its content as a parsedDoc object in the index.

            pd = p.docParser(entry.path().string());
            ih.store(pd);  // while parsing, add files to trees
        }
    }
}

void UserInterface::CreateIndex() {
    ih.resetIndex();  // resets the existing index. it overwrites the current index

    std::string directoryPath;
    std::cout << "Enter directory path to be indexed: ";
    std::cin >> directoryPath;
    std::cout << std::endl;

    // iterate through the directory and its subdirectories
    auto it = filesystem::recursive_directory_iterator(directoryPath);
    for (const auto &entry : it) {
        // check if the entry is a regular file with a .json extension
        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            count++;
            std::cout << count << ": ";
            // inintialize objects to perform parsing and indexing
            Parser p;
            ParsedDoc pd;

            // parse the JSON file and store its content as a parsedDoc object in the index.
            pd = p.docParser(entry.path().string());
            ih.store(pd);  // while parsing, add files to trees
        }
    }
}

// seperate function outside of ui interface, takes in command line argument directoryPath, instead of a choice, and creates an index of files in directoryPath if valid
void UserInterface::handleIndexCommand(const std::string &directoryPath) {
    // check if the directory exists
    if (!std::filesystem::exists(directoryPath)) {
        std::cerr << "Error: The specified directory does not exist." << std::endl;
        return;  // Exit the function
    }

    // check if it's a valid directory
    if (!std::filesystem::is_directory(directoryPath)) {
        std::cerr << "Error: The specified path is not a valid directory." << std::endl;
        return;  // Exit the function
    }

    // let the user know that indexing is in progress
    std::cout << "Evaluating Directory: " << directoryPath << std::endl;

    // iterate through the directory and its subdirectories
    auto it = std::filesystem::recursive_directory_iterator(directoryPath);
    for (const auto &entry : it) {
        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            Parser p;
            ParsedDoc pd;
            pd = p.docParser(entry.path().string());
            ih.store(pd);  // while parsing, add files to trees
        }
    }
}

void UserInterface::handleQueryCommand(const std::string &queryString) {
    // Logic to handle the 'query' command
    ih.read("../avl_trees/persons.txt", "p");
    ih.read("../avl_trees/orgs.txt", "o");
    ih.read("../avl_trees/words.txt", "w");

    // parse the input query string
    Parser parser;
    ParsedQuery p;
    p = parser.queryParser(queryString);

    // search the parsedQuery
    ih.search(p);
    // search avl tree for query
}
