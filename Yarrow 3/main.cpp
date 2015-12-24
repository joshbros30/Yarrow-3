#include <iostream>
#include <string>
#include <vector>

#include "DES.hpp"
//#include "SHA.hpp"
#include "Generation.hpp"
#include "SHANew.hpp"
//#include "EntropyAccumulator.h"

using namespace std;

GENERATOR changeKey(GENERATOR firstGen) {
    //Create temp variable for new key
    string replaceKey = "";
    
    
    //Run the generator until the length produced is less than the required length for the key
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
    
    //CryptoPP::AutoSeededRandomPool prng
    int x;
    
    cout << "What function would you like to run? " << endl;
    cout << "1. SHA1" << endl << "2. DES" << endl << "3. Run Full Generator" << endl;
    cout << "4. Reseed Test" << endl << "5. Close the programme." << endl;
    
    cin >> x;
    
    switch(x) {
            
        case 1:
        { //Call the SHA function to produce SHA1 hashing.
            SHANew h;
            //int y;
            
            
            GENERATOR test;
            
            test.initialiseKey();
          
            h.SHA1("HELLO",10,test.getKey());
            cout << "Finished Running SHA Script" << endl;
            break;
        }
        case 2:
            //Run DES.cpp
            cout << endl << "Running DES Script" << endl;
            DES1 j;
            j.DES();
            
            cout << "Finished Running DES Script" << endl;
            break;
            
        case 5:
            cout << endl << "Closing the programme :) " << endl;
            return 0;
            
//        case 4:
//            cout << endl << "Running Ressed Mechanism Test" << endl;
//     //       RESEEDER Cool;
//            Cool.RESEEDTest();
//            break;
            
        case 3:
            
            //WHY DONT YOU MAKE IT COUNT YOURSELF USING INT YOU DIV!!!
            
            cout << endl << "Running GEN Script" << endl;
            
            // Declare Generator
            GENERATOR firstGen;
            
            //Reset Counter for Generator
            firstGen.resetCtrEasy();
            
            //Initialize the key
            firstGen.initialiseKey();
            
            cout << "Initial key is: " << firstGen.getKeyString() << endl;
            
            
            //Declare variables and use them to calculate the running iterations for generation loop
            int l, k = 0;
            cout << "How many loops would you like to run the generator for?" << endl;
            cin >> l;
            cout << endl;
            
            while (k < l) {
            
                //Run the generator 10 times as P_g = 10 for the generator gate.
                for (int i = 0; i < 10; i++) {
                    
                    string Generated = firstGen.GEN();
                }
                
                /*
                 GENERATOR GATE
                Change the key, and return the generator with the new key 
                */
                
                firstGen = changeKey(firstGen);
                
                //Add one to the while counter
                k = k + 1;
                
            }
            
            //cout << "Key Previous to reseed: " << firstGen.getKeyString() << endl;
            
            //reseedStep1 changes the key to new key
            firstGen.reseedStep1(100);
            
//            
//            // THIS COUNTER RESET PROVIDES NO SECURITY EXTRAS - IT MERELY ADDS IMPLEMENTATION FLEXIBILITY ///
//            //reset counter to 0
//            firstGen.resetCtrEasy();
//            
//            string newCounterString = firstGen.GEN();
//            
//            //convert string to integer
//            int64_t x;
//            stringstream sst;
//            sst << hex << newCounterString;
//            sst >> x;
//            
//            //set new counter value
//            firstGen.setCtr(x);
//            
//            cout << "x value is: " << x << endl;
//            
//
            
            //cout << "Key after reseed: " << firstGen.getKeyString() << endl;
            break;
            
    }
    
    cout << "Your the fucking boss, it works mother fucker!" << endl;
    
    return 0;
}