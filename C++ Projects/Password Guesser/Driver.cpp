//Main Driver
//@author Jacqueline Rodriguez

#include "TokenGenerator.cpp"
#include "PasswordGuesser.cpp"
#include "UniqueTokenDetector.cpp"

int main(int argc, const char* argv[]) {
    //Invalid # arguments will exit
    if (argc != 2)
        exit(1);

    string fString;
    string fileLocation;
    int tokens;
    list<string> passwordTokens;

    fileLocation = argv[1];
    file.open(fileLocation);

    //Unique Token Detector
    uniqueTokenGuessor uTokenDetect;
    uTokenDetect.passwordTokens = getUnique(file);

    cout << "\nNumber of Tokens for Password(Possible: 1-5):  ";
    cin >> tokens;
    if (tokens < 1 || tokens > 5 || tokens > uTokenDetect.passwordTokens.size()) {
        cout << "\nInvalid Number of Tokens\n";
        exit(0);
    }

    //Password Guessor
    passwordGuesser pGuess;
    cout<< "Password: " << pGuess.guessPassword(tokens, passwordTokens);

    return 0;
}
