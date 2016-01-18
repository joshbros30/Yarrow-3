//main.cpp
//
// Main script to show GENERATOR object producing random output and
// give an example of reseed method

#include <iostream>
#include <string>
#include <vector>


#include "Generation.hpp"

using namespace std;



GENERATOR changeKey(GENERATOR firstGen) {
    //Create temp variable for new key
    string replaceKey = "";
    
    
    //Run the generator until the length produced is larger than the required length for the key
    while (replaceKey.length() < 48) {
        
        replaceKey += firstGen.GEN();
    }
    
    cout << "Key length is currently: " << replaceKey.length() << endl;
    
    //If statement - If the length is now higher, calculates the number of characters over and removes them
    if (replaceKey.length() > 48) {
        int ExtraLength = replaceKey.length() - 48;
        cout << "Extra Length: " << ExtraLength << endl;
        
        replaceKey.erase(replaceKey.end() - ExtraLength, replaceKey.end());
        
    }
    
    cout << "key Length is now: " << replaceKey.length() << endl;
    
    // Replace the key
    
    cout << "The New Key String is: " << replaceKey << endl;
    firstGen.setKey(replaceKey);
    
    cout << "Successfully changed the key!" << endl;
    
    return firstGen;
    
    
}



int main() {
    
    
    cout << endl << "Running GEN Script" << endl;
    
    // Declare Generator
    GENERATOR firstGen;
    
    //Reset Counter for Generator
    firstGen.resetCtrEasy();
    
    //Initialize the ke
    firstGen.initialiseKey();
    
    cout << "Initial key is: " << firstGen.getKeyString() << endl;
    
    //Open file to write output to
    ofstream output("/Users/Home/output.txt");
    if (!output.is_open()) {
        char answer;
        
        cout << "Error opening file to write to. Would you like to still continue? [y]es or [n]o?" << endl;
        cin >> answer;
        if ( answer == 'n') {
            exit(0);
        }
    }
    char reseed = 'y';
    
    while(reseed == 'y') {
        
        //Declare variables and use them to calculate the running iterations for generation loop
        int l, byteCount = 0, count = 0;
        cout << "How many random bytes of random output would you like to produce before reseed?" << endl;
        cout << "This must be a multiple of 8. If value entered is not,  amount will be rounded up to nearest multiple." << endl;
        cin >> l;
        cout << endl;
        
        // While loop to generate the required amount of bytes
        while (byteCount < l) {
            string Generated = firstGen.GEN();
            output << Generated;
            
            // Add 8 to the byte counter and 1 to the run counter
            byteCount = byteCount + 8;
            count = count +1;
            
            //Gate to enusure keychange happens every ten outputs
            if (count == 10){
                firstGen = changeKey(firstGen);
                count = 0;
            }
        }
        
        
        //Reseed the key with new entropy
        firstGen.reseedStep1(100);
        
        cout << "Would you like to run the generator again? [y]es or [n]o" << endl;
        cin >> reseed;
        
        
    }
    
    //Close the output file now completely finished with
    output.close();
    cout << "Please find the output at /Users/Home/output.txt" << endl;
    
    return 0;
}