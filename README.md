# json-search-engine

THe executable is called `supersearch` and has the following command line interface.
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

