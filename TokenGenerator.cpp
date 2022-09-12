/* 
Token Generator:
Students must create a class/struct (or function) that parses the input file and stores every unique token it finds. A token is any white-space delineated word. The software must strip any trailing punctuation and discard capitalization. For example, given the following quote from RADM Grace Hopper:

"Leadership is a two-way street, loyalty up and loyalty down."

The software will detect the following unique tokens:

["leadership", "is", "a", "two-way", "street", "loyalty", "up", "and", "down"]
Having detected these tokens, the function or class shall return them as a std::list of strings. Programs need not sort this list, but it may prove helpful later on. Students may use std::string for this task. If students implement this portion as a class, they should specify a public method named getUnique that returns these items.

@author: Ali Hadi
**/

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <map>
#include <algorithm>


using namespace std;

list<string> Token_Generator(string inputFile){
    // create a file object
    ifstream file;
    file.open(inputFile);

    // Verify if the input file is valid
    if (! file.is_open()){
        
        cout << "Could not find " << inputFile << " \nExiting..." << endl;
        exit(EXIT_FAILURE);
    }

    cout << inputFile << " Is open..." << endl;

    // Extract unqiue tokens by using a map
    map<string, int> m;
    string word;
    
    while (file >> word) {
          // Check if the next string ispunct
        if (any_of(word.begin(), word.end(), ::ispunct)){
            continue; 
        }

        // If word is not present, add it
        else if (m.find(word) == m.end()) {
            m.insert(make_pair(word, 1)); 
        }
        
        else {
           continue; 
        }
    }
    
    file.close();

    // copy contents over to the list
    list<string> returnList;
    for (map<string, int> :: iterator p = m.begin();
         p != m.end(); p++){
    if (p->second == 1)
            returnList.push_back(p->first);
    }

    return returnList;
}