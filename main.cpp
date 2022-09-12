/*
 * The Password Game
 *
 * Dylan James - Section 2
 * Jacqueline Rodriguez - Section 2
 * Vikram Handa - Section 1
 * Ali Hadi - Section 2
 *
 */

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

class TokenDetector {
    public:
        static list<string> Token_Generator(const string& inputFile);
        static void getUnique(const list<string>& list);
};

class PasswordGenerator{
    public:
        list<string> uniqueTokens;

        explicit PasswordGenerator(list<string>);
        string getRandomPassword(int numWords);
        string password;

        list<string>::iterator listIterator = uniqueTokens.begin();
        list<string>::iterator guessIterator = uniqueTokens.begin();

        void setIterationLength(int numWords);
        int iterationLength;
        string next();

        bool hasNext();
        string generatedPassword;

};

class PasswordGuesser{
    public:
        list<string> tokenListToGuess;
        int numTokensToGuess;

        PasswordGuesser(int numTokens, const list<string>& tokenList);
        void CrackPassword() const;
};



list<string> TokenDetector::Token_Generator(const string& inputFile){
    // Create a file object
    ifstream file;
    file.open(inputFile);

    // Verify if the input file is valid
    if (!file.is_open()) {
        cout << "Could not find " << inputFile << " \n Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    cout << inputFile << " Is open ..." << endl;

    // Extract unique tokens by using a map
    map<string, int> m;
    string word;

    while (file >> word) {
        // Check if the next string ispunct
        if (any_of(word.begin(), word.end(), ::ispunct)){
            continue;
        }

            // If word is not present, add listIterator
        else if (m.find(word) == m.end()) {
            m.insert(make_pair(word, 1));
        }

        else {
            continue;
        }
    }

    file.close();

    // Copy contents over to the list
    list<string> returnList;
    for (map<string, int> :: iterator p = m.begin();
         p != m.end(); p++){
        if (p -> second == 1)
            returnList.push_back(p -> first);
    }

    return returnList;
}

void TokenDetector::getUnique(const list<string>& mylist){
    list<string>::iterator();
    cout << "Token List: " << endl;

    for (auto & it : mylist){
        cout << '\t' <<  it << endl;
    }
}

PasswordGenerator::PasswordGenerator(list<string> tokenList){
    uniqueTokens = tokenList;
}

string PasswordGenerator::getRandomPassword(int numWords){
    //Create password indicie array in order to populate.
    int numTokens = numWords;
    int passwordIndices[numTokens];
    int passwordIndicesSize = sizeof(passwordIndices) / sizeof(passwordIndices[0]);
    int passwordIndicesEnd = passwordIndicesSize - 1;


    int x = 0;
    while (x < passwordIndicesSize){
        int randIndex = (rand() % uniqueTokens.size());
        bool match = false;

        //Ensure there are no duplicates.
        for (int j = 0; j < x; ++j){
            if (randIndex == passwordIndices[j]){
                match = true;
            }
        }

        if (!match){
            passwordIndices[x] = randIndex;
            x = x + 1;
        }
    }


    for (int i = 0; i < passwordIndicesSize; ++i){
        int nIndicie = passwordIndices[i];
        advance(listIterator, nIndicie);
        string nToken = *listIterator;
        listIterator = uniqueTokens.begin();

        if (i == passwordIndicesEnd){
            password = password + nToken;
        } else{
            password = password + nToken + " ";
        }
    }

    return password;
}

void PasswordGenerator::setIterationLength(int numWords){
    iterationLength = numWords;
    listIterator = uniqueTokens.begin();
}

string PasswordGenerator::next() {
    int i = 0;
    int j = 0;

    string guessedPassword;
    string pwArray[iterationLength];
    stringstream basicStringstream(password);

    while (basicStringstream.good() && i < iterationLength) {
        basicStringstream >> pwArray[i];
        ++i;
    }

    uniqueTokens.begin();
    while (j < iterationLength) {
        for (guessIterator = uniqueTokens.begin(); guessIterator != uniqueTokens.end(); ++guessIterator) {
            if (*guessIterator == pwArray[j]) {
                if (j == iterationLength - 1) {
                    guessedPassword.append(pwArray[j]);
                }else{
                    guessedPassword.append(pwArray[j]).append(" ");
                }
            }
        }
        j++;
    }
    cout << "The generated password is: " << password << endl;

    cout << " \n ... Guessing Password ... \n " << endl;
    cout << "The password is: " << guessedPassword << "\n";

    return guessedPassword;
}

bool PasswordGenerator::hasNext() {
    if ((guessIterator != uniqueTokens.end()) && (guessIterator == --uniqueTokens.end())) {
        return false;
    }else{
        return true;
    }
}

PasswordGuesser::PasswordGuesser(int numTokens, const list<string>& tokenList) {
    numTokensToGuess = numTokens;
    tokenListToGuess = tokenList;

}

void PasswordGuesser::CrackPassword() const {
    PasswordGenerator passwordGenerator = PasswordGenerator(tokenListToGuess);
    passwordGenerator.getRandomPassword(numTokensToGuess);
    passwordGenerator.setIterationLength(numTokensToGuess);
    passwordGenerator.next();
}

int main(int argc, char** argv){
    //Check for proper arguments, otherwise exit.
    if (argc != 2)
        exit(1);

    //User input numTokens.
    int numTokens;

    //Set seed using time, used for random password generation. (In main so it is only set once).
    srand(time(nullptr));

    string inputFile = argv[1];

    TokenDetector tokenMethods;
    list<string> tokenList = tokenMethods.Token_Generator(inputFile);

    tokenMethods.getUnique(tokenList);

    PasswordGenerator passwordGenerator(tokenList);

    cout << "Number of Tokens for Password(Possible: 1-5):";
    cin >> numTokens;

    if (numTokens < 1 || numTokens > 5 || numTokens > passwordGenerator.uniqueTokens.size()) {
        cout << "\nInvalid Number of Tokens\n";
        exit(0);
    }

    PasswordGuesser passwordGuesser = PasswordGuesser(numTokens,passwordGenerator.uniqueTokens);
    passwordGuesser.CrackPassword();


    return 0;
}