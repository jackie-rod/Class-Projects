//Author: Jacqueline Rodriguez
//CS Programming Languages Class Project
//Demonstrating C++
//Section 2
//Metal Head Program

//--------------------INCLUDES------------------------//
//--------------------INCLUDES------------------------//
#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

//--------------------CLASS---------------------------//
//--------------------CLASS---------------------------//
class Guitar{
    private: 
        unsigned char numberOfFrets = 21;
        std::vector<double> current;
    public:
    //--------------------DE/CONSTRUCTORS-----------------//
    //--------------------DE/CONSTRUCTORS-----------------//
    //DEFAULT
    // initializes the guitar to EADGBE tuning and a 21 fret guitar
    Guitar(){
        current.push_back(82.41);
        current.push_back(110);
        current.push_back(146.8);
        current.push_back(196);
        current.push_back(246.9);
        current.push_back(329.6);
    }

    //COPY CONSTRUCTOR
    // copy constructor (if the guitar allocates heap memory)
    Guitar(const Guitar &guitar){
        current = guitar.current;
        numberOfFrets = guitar.numberOfFrets;
    } 

    //DESTRUCTOR
    ~Guitar(){
        std::cout << "Destroy Entity Success." <<std::endl;
    }

    //--------------------METHODS-------------------------//
    //--------------------METHODS-------------------------//

    bool setFretBoardLength(const unsigned char numFrets){
        if ((numFrets >= 1) && (numFrets <= 24)) {
            numberOfFrets = numFrets;
            return true;
        }
        else
            return false;
    //TODO
        // sets the corresponding private field and verifies the input is between 1 and 24
    }
    
    unsigned double pitchAt(const unsigned char &stringNumber, const unsigned char &fret){
        if (stringNumber == 1)
            return current[0] * pow(2, fret / 12.0);
        else if (stringNumber == 2)
            return current[1] * pow(2, fret / 12.0);
        else if (stringNumber == 3)
            return current[2] * pow(2, fret / 12.0);
        else if (stringNumber == 4)
            return current[3] * pow(2, fret / 12.0);
        else if (stringNumber == 5)
            return current[4] * pow(2, fret / 12.0);
        else if (stringNumber == 6)
            return current[5] * pow(2, fret / 12.0);
        else return 0;
    //TODO
        // Returns the corresponding frequency in Hz for the given string and fret. 
        // Unlike array indices, these use natural numbers, so the low E string shall be 
        // string 1 and the high E string shall be 6
    }
    
    std::pair<unsigned char, unsigned char> getStringAndFret( double pitch ){
        std::vector<std::pair<unsigned char, unsigned int>> all;
        std::vector<double> allPitch;
        
        for (char i = '1'; i <= '6'; i++) 
            for (int j = 0; j <= numberOfFrets; j++) {
                all.push_back(std::make_pair(i, j));
                all.push_back(current[i - '0' - 1] * pow(2, j / 12.0));
            }

        double diff = abs(all[0] - all);
        int in = 0;
        for (int i = 1; i < all.size(); i++ )
            if ( abs(all[i] - all) < diff ){
                in = i;
                diff = abs(all[i] - all);
            }
    return all[in];

    //TODO
        // Given the all, the method shall return a std::pair object with the string/fret combination 
        // that comes closest to producing that all. There may be multiple solutions. The function 
        // shall return the first it identifies
    }
    
    void tuneString(unsigned char& string, const double& pitch){
        if (string == 1) current[0] = pitch;
        if (string == 2) current[1] = pitch;
        if (string == 3) current[2] = pitch;
        if (string == 4) current[3] = pitch;
        if (string == 5) current[4] = pitch;
        if (string == 6) current[5] = pitch;

    //TODO
        // changes the tuning for an individual string.
    }
};

//-------------------DRIVER--------------------//
//-------------------DRIVER--------------------//
//-------------------DRIVER--------------------//
int main(){
    Guitar guitar;
    
    unsigned char test = '0';
    guitar.tuneString(test, 82.41);
    
    std::cout << "Pitch Test Case - B, fret 4: " << guitar.pitchAt('4', 4) << "Hz" << std::endl;
    std::cout << "Pitch Test Case - D, fret 1: " << guitar.pitchAt('2', 1) << "Hz" << std::endl;
    
    
    return 0;
}
