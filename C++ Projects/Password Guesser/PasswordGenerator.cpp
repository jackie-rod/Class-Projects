#include <iostream> 
#include <random>
#include <fstream>
#include <streambuf>
#include "tokenGenerator.cpp"

using namespace std;

class passwordGuesser{
    string guessPassword(string *words, int n) {
        default_random_engine generator;
        uniform_int_distribution<int> distribution(0,n)
        string password;

        while(!checkPassword(password)) {
            int i,j,k;
            i = distribution(generator);

            do {
                j = distribution(generator);
            } while (j==1);

            do {
                k = distribution(generator);
            } while (k==i || k==j);

            password = words[i] + words[j] + words[k];
        }
        return password;

    }

    string bruteForce(string *words, int n){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                for(int k = 0; k < n; k++){
                    if (checkPassword(words[i] + words[j] + words[k])) {
                        return (words[i] + words[j] + words[k]);
                    }
                } 
            }
        }
    }

    bool checkPassword(string password) {
        if (password.compare(generatedPassword)) == 0){
            return true;
        } else {
            return false;
        }

    }

};
