# json-search-engine

The executable for the search engine is called `supersearch` and has the following command line interface.
The first argument is the command followed by additional information for the command. Here are examples:

Usage:

* Index all files in `<directory>` and store the index in one or several files:
  
  ```
  supersearch index <directory>
  ```

* Load the existing index and perform the following query:
  
  ```
  supersearch query "social network PERSON:cramer"
  ```

* Start a simple text-based user interface that lets the user create an index,
  save/load the index and perform multiple queries:
  
  ```
  supersearch ui
  ```

### High-level Design of Solution

## UML Class Diagram:
    See Search Engine (Design).pdf in repository

## High Level Pseudocode for main() function:
#### main(argc, argv):
    
    Initialize UserInterface as menu
    Handle indexing for predefined directory "sample_data"

    If argc >= 2:
        Parse command from argv[1]

        If command is "index" and argc is 3:
            Handle indexing for directory specified in argv[2]

        Else if command is "query" and argc is 3:
            Handle query with string specified in argv[2]

        Else if command is "ui":
            Start UI loop
                Display UI menu and handle choices until exit

        Else:
            Display error and usage instructions

    Else:
        Display error and usage instructions

## High Level Pseudocode for UI Class:
#### UIDisplay():
    
    Loop:
        Display main menu options
        Get user choice
        If choice is valid (1-4):
            Exit loop

    Return choice

#### DisplayChoice(choice):
    
    If choice is 1 (Create/Update Index):
        Display submenu for index creation or update
        Get user choice for index operations
        Call respective functions (UpdateIndex/CreateIndex) or return to main menu

    Else if choice is 2 (Read/Write Index):
        Display submenu for index read/write
        Get user choice for read/write operations
        Call respective functions (read/write) or return to main menu

    Else:
        Handle query input and processing

#### UpdateIndex/CreateIndex():
    
    Get directory path from user
    Get directory path from user input

    Iterate over all files in the directory
    For each file in the directory:
        If the file is a .json file:
            // Parse the document and store it in the index handler
            Parse the document and store it in the index handler

#### handleIndexCommand(directoryPath):
    
    Check if the specified directory exists
    If the directory does not exist:
        Display an error message and return

    // Check if the specified path is a valid directory
    If the path is not a valid directory:
        Display an error message and return

    // Notify the user that indexing is in progress
    Display a message indicating that indexing is in progress

    // Iterate through the directory and its subdirectories
    For each file in the directory and subdirectories:
        If the file is a regular file with a .json extension:
            // Parse the document and store it in the index handler
            Parse the document and store it in the index handler

#### handleQueryCommand(queryString):
    
    Read index data from files for persons, organizations, and words
    
    Create a parser object
    
    Parse the user's query using the parser

    Perform a search operation on the index data based on the parsed query

## High Level Psuedocode for Parser Class (Integrates ParsedDoc and ParserQuery)
#### queryParser(query):

    Loop until the input query string q is empty
    
        Find the position of "PERSON:", "ORG:", and "-" in the query string q
        Find positions of special tokens in the query string

        If "PERSON:" is found
        If "PERSON:" is found:
            // Extract the person name
            Extract and clean the person name
            Add the person name to the ParsedQuery object
            Erase the extracted word from the query string

        If "ORG:" is found
        Else if "ORG:" is found:
            // Extract the organization name
            Extract and clean the organization name
            Add the organization name to the ParsedQuery object
            Erase the extracted word from the query string

        If "-" is found (for negWords)
        Else if "-" is found:
            // Extract the negWord
            Extract and clean the negWord
            Add the negWord to the ParsedQuery object
            Erase the extracted word from the query string

        If none of the special tokens are found, consider it as a regular word
        Else:
            // Extract the word
            Extract and clean the word
            Add the word to the ParsedQuery object
            Erase the word from the query string

    Continue looping until the query string is empty

    Return the ParsedQuery object containing the extracted query data
    Return the ParsedQuery object

#### removeNonAlphanumeric(str):
    Use regular expression to remove non-alphanumeric characters
    Return cleaned string

#### cleanToken(token):

    Remove non-alphanumeric characters
    Convert all characters to lowercase
    Return cleaned token

#### removeStopWords(tokens, stopWords):

    Filter out stop words from the tokens list using map of stop words

#### tokenize(str, regex):

    Use regular expression to split string into tokens
    Clean each token
    Return list of cleaned tokens

##### docParser(fileName):

    Open an ifstream on the specified file
    If the file cannot be opened:
        Display an error message and return an empty ParsedDoc object

    // Create a RapidJSON IStreamWrapper using the file input stream
    Create a RapidJSON IStreamWrapper

    // Create a RapidJSON Document object and parse the IStreamWrapper
    Create a RapidJSON Document and parse the JSON content

    Extract the path of the document and add it to the ParsedDoc object
    
    Tokenize the document text and remove stop words

    // Iterate over persons in the document and tokenize their names
    For each person in the document:
        Tokenize the person's name and add cleaned tokens to ParsedDoc object

    // Iterate over organizations in the document and tokenize their names
    For each organization in the document:
        Tokenize the organization's name and add cleaned tokens to ParsedDoc object

    Close the input file stream

    Return the populated ParsedDoc object

## High Level Psuedocode for ParsedDoc/ParsedQuery Class

#### ParsedDoc()/ParsedQuery():

    Initialize empty lists for persons, orgs, words, etc.

#### addPerson/Orgs/Words/NegWords(title, s):

    Add the given string to the respective list

#### getPersons/Orgs/Words/NegWords():

    Return the respective list

#### printPersons/Orgs/Words/NegWords():

    Print elements of the respective list

## High Level Pseudocode for IndexHandler Class

#### treesEmpty():
Check if all AVL trees (persons, words, orgs) are empty
    Check if all AVL trees are empty
        If persons AVL tree is empty and words AVL tree is empty and orgs AVL tree is empty:
            Return true
        Else:
            Return false

#### write():
    Write the current state of AVL trees to appropriate files
        Write the contents of AVL trees to corresponding files

#### read(std::string path, std::string name):
    Read data from a specified file and populate the corresponding AVL tree
        Depending on the name ("p" for persons, "o" for orgs, "w" for words), make the corresponding AVL tree empty
            If name is "p":
                persons.makeEmpty()
            Else If name is "o":
                orgs.makeEmpty()
            Else:
                words.makeEmpty()

    Read data from the specified file
    Open the file at the specified path

    If the file is open:
        While there are more words to read from the file:
            Read a word from the file
            Create an AvlPair with the word
            Read document names associated with the word until "-" is encountered
            For each document name:
                Add the document name to the AvlPair
                Read and update the count for the word in that document
            Depending on the name ("p" for persons, "o" for orgs, "w" for words):
                Insert the AvlPair into the corresponding AVL tree
        Close the file
    Else:
        Display an error message

#### search(ParsedQuery pq):
    Search for documents based on a ParsedQuery and print the results
        Create a map to store document paths and their relevance scores

    Loop through the persons in the ParsedQuery
    For each person in pq.getPersons():
        Get the AvlPair associated with the person from the persons AVL tree
        If the person is found:
            For each document in the AvlPair:
                Update the relevance score for that document in the map
    Repeat the above process for organizations, words, and negWords in the ParsedQuery

    Print the search results based on relevance scores
    Call printSearchResults with the documentScores map as an argument

#### printSearchResults(std::map<std::string, int> &documentScores):
    Print search results based on relevance scores
        Create a map to store document paths and their rank

    // While there are documents to rank or until a certain count is reached:
    While documentScores is not empty and count <= 15:
        Find the document with the highest relevance score in documentScores
        Store the document path in rankedDocuments with its rank (count)
        Remove the document from documentScores
        Increment count

    // Print the ranked documents along with their titles, publishers, and dates
    For each ranked document in rankedDocuments:
        Open the document file
        If the file is open:
            Parse the JSON content of the document
            Print the document title, publisher (if available), and date of publication
            Print the document text
            Close the file
        Else:
            Display an error message

    Allow the user to go back and open another document (if desired)
    Repeat until the user decides not to continue
    
#### resetIndex():
    Reset the index by clearing AVL trees and associated files
        Clear all AVL trees
    
        Clear associated files by truncating them
        Open and truncate the "persons.txt" file
        Open and truncate the "orgs.txt" file
        Open and truncate the "words.txt" file

#### store(ParsedDoc &pd):
    Store data from a ParsedDoc object into the corresponding AVL trees
        Convert and insert data from ParsedDoc into persons, orgs, and words AVL trees

## Used Data Structures
Explanation of what data structures are used where. For each, state
    - time and space complexity (Big-Oh),
    - why it is the appropriate data structure and what other data structure could have been used. 

#### AVL tree: 
    - Usage: for maintaining a sorted collection of elements while ensuring that the tree remains balanced. 
    The balance property of AVL trees makes them particularly efficient for searching, inserting, and deleting elements, 
    as it guarantees that the height of the tree remains relatively small and balanced.
    - Properties: An AVL tree is balanced in a way that for every node in the tree, the heights of its left and right subtrees 
    differ by at most one. This balance property ensures that the tree remains relatively shallow, which leads to efficient 
    operations. AVL trees maintain their balance property automatically during insertions and deletions. This self-balancing 
    property makes them suitable for indexes where files are frequently added or removed. AVL trees store elements in a sorted order. 
    In an AVL tree, elements to the left of a node are smaller than the node, and elements to the right are larger, following the binary 
    search tree property. This makes AVL trees suitable for applications where maintaining data in a sorted order is essential.
    
    -The height of an AVL tree with 'n' nodes is guaranteed to be O(log n), which means that search operations take logarithmic time 
    in the number of elements. 
    - The rebalancing ensures that insertion and deletion operations also take O(log n) time on average. 

#### std::map<std::string, int>` in `AvlPair.h`:

    - Usage: to associate words with counts (documents). Each unique document is stored as a key, 
    and its count is the associated value. 
    
    - Properties: provides efficient insertion, search, and update operations with a time complexity 
    of O(log n), where n is the number of unique documents. So operations on the map remain reasonably 
    fast even as the number of documents grows. Maintains keys in a specific order, based on the keys' natural 
    order which to access documents in a sorted manner or perform range queries faster.

##### Time Complexity:
- Insertion (addDoc): O(log n)
- Search (findDoc): O(log n)
- Update (plusCountAtLoc, changeCount): O(log n)
- Retrieval (returnDocAt, returnCountAt): O(log n)

#### Standard Template Library (STL) Vectors (std::vector)

    - Usage: Vectors are used extensively in both of our ParsedDoc and ParsedQuery classes 
    to store lists of persons, organizations, words, and negative words.
    
    - Properties: We chose a vector because it is a dynamic array that can resize itself and 
    provides random access toelements which is great for accessing and appending data when parsing 
    through data. Especially useful for when the number of elements is unkknown beforehand.

##### Time Complexity:

#### Unordered Set (std::unordered_set)

    - Usage: An unordered set is used in our project for storing stop words in the removeStopWords method.
    
    - Properties: Offers a constant time O(1) complexity for searching operations which is good for quick 
    lookups and checking if a token is a stop word.

##### Time Complexity:

#### Alternative Data Structure Considerations:

    - std::unordered_map: If the focus is primarily on fast insertion and retrieval, 
    an `std::unordered_map<std::string, int>` could be used. This would provide O(1) 
    average-case time complexity for these operations. Might be implemented in the future!
    
    - std::vector<std::pair<std::string, int>>: If we did not need efficient search by document name and
    chose to iterate through all documents, a vector of pairs could be used. This would provide O(1) time complexity 
    for most operations due to direct access, but it wouldn't be as efficient for searching by document name. Since
    we have thousands and thousands of documents this is not a good choice.

### User Documentation

## Features of Search Engine: 
#### Directory/File Document and Query Parsing:

    - Capable of parsing both structured documents (JSON files) and user queries.
    - Extracts and processes specific elements like titles, persons, organizations, and general text.

#### Handling of Specific Query Patterns:

    - Recognizes special query patterns such as "PERSON:", "ORG:", and negation ("-") to categorize parts of the user query.
    - Allows for more specific search queries, enhancing the result functionality.

## How to use the Search Engine.
#### Running the Software
#### Command Line Execution:
  - To start the program, use the command line to execute the `supersearch` executable. For example:
    ```
    ./supersearch [command] [additional arguments]
    ```

#### Indexing Documents
- **Command**: `index`
- **Usage**:
  - To index all JSON files in a directory, use:
    ```
    supersearch index <directory>
    ```
- **Functionality**:
  - Parses each JSON file in the specified directory.
  - Extracts information such as titles, persons, and organizations.
  - Constructs an AVL tree-based inverted index for each term (PERSON, ORG, and WORD).

#### Performing Queries
- **Command**: `query`
- **Usage**:
  - To perform a search query, use:
    ```
    supersearch query "your query here"
    ```
  - Example:
    ```
    supersearch query "social network PERSON:cramer ORG:facebook -germany -finance"
    ```
- **Functionality**:
  - Processes queries, recognizing patterns such as "PERSON:", "ORG:", and "-" for negative words.
  - Searches the constructed AVL tree indices for relevant terms.

#### Using the UI (User Interface)
- **Command**: `ui`
- **Usage**:
  - To start the text-based user interface, use:
    ```
    supersearch ui
    ```
- **Functionality**:
  - Offers a menu-driven interface for various operations.
  - **Creating/Updating Indexes**:
    - Allows creation of a new index or updating an existing one.
    - Processes documents in a specified directory.
  - **Reading/Writing an Index**:
    - Enables reading from or writing to an index file for persistence.
  - **Conducting Searches**:
    - Allows the user to enter and process queries.

## Example Queries with the Results.

### Ex. Query 1: "PERSON:mark PERSON:zuckerberg ORG:eaton government germany brexit -britain"
    grantpalmer@Grants-MBP-2 build % ./supersearch query "PERSON:mark PERSON:zuckerberg ORG:eaton government germany brexit -britain"

    1. CNBC Interview with Mark Weinberger, EY’s Global Chairman, from the World Economic Forum 2018 - 2018-01-23T09:59:00.000+02:00
    
    2. All of the world’s largest economies are now expanding, lifting fortunes and spirits - 2018-01-27T23:47:00.000+02:00
    
    3. Commentary: There’s a better way to unite Europe - 2018-01-06T01:45:00.000+02:00
    
    4. German Social Democrats wary as coalition talks enter crunch stage - 2018-01-10T12:40:00.000+02:00
    
    5. EU unity paramount to Germany in Brexit talks, insists Berlin - 2018-01-10T14:39:00.000+02:00
    
    6. PRECIOUS-Gold down on concern about Europe, buoyant shares - 2018-01-09T19:16:00.000+02:00
    
    7. German Social Democrats wary as coalition talks enter crunch stage - 2018-01-10T12:41:00.000+02:00
    
    8. The burning questions that investors need to answer for 2018 - 2018-01-09T08:47:00.000+02:00
    
    9. Austria arrests 45 for drug deals involving migrant minors: police - 2018-01-15T14:09:00.000+02:00
    
    10. Twenty-one hours and counting: German coalition talks drag on - 2018-01-12T07:27:00.000+02:00
    
    11. Daily Briefing: Merkel coalition pact - misgivings emerge - 2018-01-15T10:23:00.000+02:00
    
    12. UPDATE 3-German parties offer Macron first response on Europe - 2018-01-12T18:01:00.000+02:00
    
    13. Twenty-one hours and counting: German coalition talks drag on - 2018-01-12T07:27:00.000+02:00
    
    14. EU unity paramount to Germany in Brexit talks, insists Berlin - 2018-01-10T20:39:00.000+02:00
    
    15. Berlin and Paris step up push for euro zone reform deal - 2018-01-14T19:05:00.000+02:00
    
    Select an article to open (enter number): 1


### Ex. Query 2: PERSON:Putin PERSON:Trump ORG:Lockheed ORG:Martin weapons defense -peace -happiness
    grantpalmer@Grants-MBP-2 build % ./supersearch ui
    ==============================================
                   ~Search Engine~                
    ----------------------------------------------
    1. Create or Update Index
    2. Read/Write to Index
    3. Search Queries
    4. Exit Program
    ==============================================
    Select an option (1 | 2 | 3 | 4): 3
    
    ENTER QUERY: PERSON:Putin PERSON:Trump ORG:Lockheed ORG:Martin weapons defense -peace -happiness  
    
    1. Defense manufacturers cashing in on Trump's global arms push - 2018-01-25T00:57:00.000+02:00
    
    2. U.S. State Department official to promote military sales at Singapore show - 2018-02-02T03:07:00.000+02:00
    
    3. U.S. State Department official to promote military sales at Singapore show - 2018-02-02T01:25:00.000+02:00
    
    4. Pentagon Plans to Spend Billions on F-35 Jets Despite Problems | Fortune - 2018-02-06T16:39:00.000+02:00
    
    5. Cramer's game plan: Welcome to the Super Bowl of earnings - 2018-01-27T01:12:00.000+02:00
    
    6. Lockheed enhances capability of its Aegis missile-defense system - 2018-01-11T15:50:00.000+02:00
    
    7. Lockheed enhances capability of its Aegis missile-defense system - 2018-01-11T15:50:00.000+02:00
    
    8. Only Half of Lockheed-Martin F-35 Jets Are Ready to Fly | Fortune - 2018-01-24T11:07:00.000+02:00
    
    9. U.S. Defense Firms Want to Keep Tax Windfall - 2018-01-29T21:05:00.000+02:00
    
    10. UPDATE 1-Lockheed Martin revenue beats, expects higher profit in 2018 - 2018-01-29T20:57:00.000+02:00
    
    11. Boeing, Lockheed Martin are the ‘early winners’ under Trump’s budget proposal: JP Morgan - 2018-02-13T18:33:00.000+02:00
    
    12. US firms dominate Singapore Air Show amid Trump's "Buy American" policy - 2018-02-08T05:34:00.000+02:00
    
    13. German ministry sees benefit in keeping fighter jet expertise in Europe - 2018-02-28T21:17:00.000+02:00
    
    14. CIA believes North Korea weapons aimed at coercion, not just defense: Pompeo - 2018-01-23T19:23:00.000+02:00
    
    15. Trump's State of the Union choice: Tackle the Russia probe head on, or pretend it doesn't exist - 2018-01-30T14:00:00.000+02:00
    
    Select an article to open (enter number): 1
    
    Foreign arms sales are growing in importance to the top line of big defense firms and may get an added boost this year due to initiatives by President Donald Trump .
    Sales to allies and other friendly countries also have allowed American defense companies to extend production lines that otherwise might be shuttered or downsized.
    Trump's personal involvement in defense sales also hasn't gone unnoticed, whether touting $350 billion in weapons to Saudi Arabia last May or suggesting in November that Japan should buy more U.S.-made equipment to shoot North Korean missiles "out of the sky."
    Lockheed Martin and Raytheon , two defense companies with upcoming earnings reports, stand to benefit from increased international sales over the next few years, according to analysts. A lot of the recent growth in U.S. defense sales is in missile defense systems and Lockheed's F-35 stealth fighter jets.
    "We're seeing a global upturn in defense spending," said Peter Arment, a defense analyst at Robert W. Baird. "We're seeing Europe, NATO, the Middle East, Asia and U.S. domestic."
    Getty Images Patriot Missile For defense companies, international weapons sales can sometimes be more lucrative too. Arment said direct arms sales from U.S. defense companies to foreign countries "can have a higher margin" than going through Washington's Foreign Military Sales program.
    Reuters reported earlier this month that the administration plans as part of its new "Buy American" plan to have embassy personnel "help drum up billions of dollars more in business overseas for the U.S. weapons industry."
    "This is the government's job in many ways," Roman Schweizer, a Cowen defense analyst and former government acquisition official, told CNBC.
    Regardless of the administration's new plans, Schweizer said there are diplomats and other federal workers at embassies around the world already actively promoting U.S. defense exports.
    "We have used foreign military sales to help friends and allies around the world and also to help U.S. defense manufacturers around the world," Schweizer said.
    However, Reuters said the White House's plans will be "going beyond the limited assistance" now provided by overseas American military attaches and diplomats.
    The White House didn't respond to CNBC's request for comment.
    Remy Nathan, vice president of international affairs at the Aerospace Industries Association, said the Arlington, Virginia-based industry trade group representing some top American defense companies "is very much in favor of enhancing" the current arrangement.
    Specifically, the administration wants to make it easier to export U.S. defense products abroad, whether drones, aircraft or ships. It comes at a time when the Chinese are getting more aggressive in selling weapons overseas.
    The Trump administration has already relaxed rules allowing more military sales to countries such as Saudi Arabia, which has been accused of war crimes by some human rights groups . Also, the administration lifted human rights conditions for arms sales to other countries, including Bahrain.
    In May, when he visited Saudi Arabia on his first foreign-nation visit, the president announced a massive, multiyear arms deal with the kingdom that he said would add hundreds of thousands of U.S. jobs. But some questioned whether all of the weapons were part of a new agreement.
    Even so, an expanded "Buy American" program in defense helps the administration in its efforts to boost manufacturing jobs.
    The U.S. had nearly $42 billion in foreign military sales during fiscal 2017, up from $33.6 billion in the previous year, according to the Defense Security Cooperation Agency. There is an expectation that foreign military sales could grow again this fiscal year due to increased global tensions and efforts by U.S. allies to increase their overall defense spending.
    Even neutral Sweden is increasing its defense spending due to worries about a more aggressive Russia. Also, a Cold War-era mentality in Sweden led the government to recently reissue information about civil defense to some 4.7 million households.
    For weapons, Sweden is looking to buy a $1.2 billion Patriot air-and-missile defense system from Raytheon.
    In November, Poland obtained U.S. State Department approval on a $10.5 billion purchase of the Patriot system. Romania, another NATO country, was cleared in July to buy the Patriot system.
    In all, Raytheon has built more than 220 units of the Patriot system, delivering them to customers in 14 nations worldwide.
    Raytheon also has benefited from recent anti-ballistic missile sales to Japan. Japan's government also recently approved the purchase of the Lockheed-made Aegis Ashore missile defense system.
    Raytheon's international sales made up about 32 percent of its total sales in the first three quarters of 2017. When it reports year-end results Thursday it's possible the company will mark the 14th consecutive year of international sales growth.
    Lockheed's F-35 stealth fighter aircraft is now the driver for its foreign defense sales growth. Of the nine original F-35 partner countries, six how have jets in their fleet. The planes are not manufactured only in the U.S. but also in Japan.
    Lockheed CEO Marillyn Hewson said in October during the previous earnings call that the company was on track in 2017 to have 30 percent of sales come from overseas, up from 27 percent in 2016. Lockheed is scheduled to report its full-year 2017 results on Monday.
    Lockheed won a $3.8 billion deal last year to sell F-16 fighter upgrades and new aircraft to the government of Bahrain. According to Hewson, the contract is expected to extend the F-16 production beyond the 2021 timeframe.
    Similarly, Boeing's F-15 fighter production stands to benefit since the U.S. government announced last month that Qatar will buy 15 of the aircraft.
    Production for the F-15QA could start next year and extend assembly-line work into 2022. Also, the contract is good news for numerous suppliers who get work for everything from the components to the avionics and airframe systems.
    WATCH: Defense contractors deploy contingency plans after shutdown show chapters Defense contractors deploy contingency plans after government shuts down 8:56 AM ET Mon, 22 Jan 2018 | 01:32
    
    Go back and open another? (yes or no) : no

### Performance:
    Larges dataset size tested = 371000: files:
        - Time to create index of files: 1895736 ms = 31.5956 minutes
        - Time to write index: 25512ms = 0.2252 minutes
    Query Search Time: QUERY: PERSON:Putin PERSON:Trump ORG:Lockheed ORG:Martin weapons defense -peace -happiness
        - Time to search a complex query from created indexed data: 3871ms = 3.871000s

