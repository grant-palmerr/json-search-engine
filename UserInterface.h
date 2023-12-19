#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <string>
#include <vector>

#include "AvlTree.h"
#include "IndexHandler.h"
#include "Parser.h"

class UserInterface {
   private:
    IndexHandler ih;  // heart of program: deals with searching queries, reading, writing, creating and updating indices,
    int count;

   public:
    UserInterface();
    int UIDisplay();                                          // called when ./supersearch ui command is entered into command line
    void DisplayChoice(const int x);                          // based on ui user choice, displays that choice
    void UpdateIndex();                                       // updates an index
    void CreateIndex();                                       // creates an index
    void handleIndexCommand(const std::string &director);     // logic that handles the 'index' command
    void handleQueryCommand(const std::string &queryString);  // logic for handling the 'query' command
};

#endif