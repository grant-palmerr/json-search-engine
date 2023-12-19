#include <iostream>

#include "AvlTree.h"
#include "ParsedQuery.h"
#include "Parser.h"
#include "UserInterface.h"

// main function for the supersearch application
int main(int argc, char *argv[]) {
    UserInterface menu;

    // check if command line arguments are provided
    if (argc >= 2) {
        std::string command = argv[1];
        // check for the "index" command with a valid argument
        if (command == "index" && argc == 3) {
            menu.handleIndexCommand(argv[2]);
            // look for the third argument which is the path to a directory
        } else if (command == "query" && argc == 3) {
            // process the "query" command with a query string argument
            menu.handleQueryCommand(argv[2]);
            // look for the second argument which is the query string
        } else if (command == "ui") {
            // start the user interface loop
            bool isUIRunning = true;
            while (isUIRunning) {
                int choice = menu.UIDisplay();
                if (choice >= 1 && choice <= 3) {
                    menu.DisplayChoice(choice);
                } else if (choice == 4) {
                    isUIRunning = false;
                }
            }
            std::cout << "Exiting the UI..." << std::endl;
        } else {
            //if user gives invalid command, display usage instructions
            std::cerr << "Invalid command, Need to insert a command into Command Line: " << std::endl;
            std::cout << "Usage:\n"
                      << "  supersearch index \"path_to_directory\" - Index all files in directory\n"
                      << "  supersearch query \"query string\" - Perform a query\n"
                      << "  supersearch ui - Start the user interface\n";
        }
    }

    else {
        // no specific command provided - display help/usage message
        std::cerr << "Invalid command, Need to insert a command into Command Line: " << std::endl;
        std::cout << "Usage:\n"
                  << "  supersearch index \"path_to_directory\" - Index all files in directory\n"
                  << "  supersearch query \"query string\" - Perform a query\n"
                  << "  supersearch ui - Start the user interface\n";
    }
    
    return 0;
}