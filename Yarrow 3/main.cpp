#include <iostream>
#include <string>
#include <vector>

#include "DES.hpp"
#include "SHA.hpp"
#include "Generation.hpp"

using namespace std;

void changeKey(GENERATOR firstGen) {
    //Create temp variable for new key
    string replaceKey = "";
    
    
    //Run the generator until the length produced is less than the required length for the key
    while (replaceKey.length() < 24) {
         
        replaceKey += firstGen.GEN();
    }
    
    cout << "Key length is currently: " << replaceKey.length() << endl;
    
    //If statement - If the length is now higher, calculates the number of characters over and removes them
    if (replaceKey.length() > 24) {
        int ExtraLength = replaceKey.length() - 24;
        cout << "Extra Length: " << ExtraLength << endl;
        
        replaceKey.erase(replaceKey.end() - ExtraLength, replaceKey.end());
        
    }
    
    cout << "key Length is now: " << replaceKey.length() << endl;
    
    // Replace the key
    firstGen.setKey(replaceKey);
    
    cout << "Successfully changed the key!" << endl;
    
    

}



int main() {
    
    //CryptoPP::AutoSeededRandomPool prng
    int x;
    
    cout << "What function would you like to run? " << endl;
    cout << "1. SHA1" << endl << "2. DES" << endl << "3. Run Full Generator" << endl << "4. Close the programme." << endl;
    
    cin >> x;
    
    switch(x) {
            
        case 1:
            //Call the SHA function to produce SHA1 hashing.
            SEC1 h;
            h.SHA();
            cout << "Finished Running SHA Script" << endl;
            break;
        case 2:
            //Run DES.cpp
            cout << "Running DES Script" << endl;
            DES1 j;
            j.DES();
            
            cout << "Finished Running DES Script" << endl;
            break;
            
        case 4:
            cout << "Closing the programme :) " << endl;
            return 0;
            
        case 3:
            
            //Generate key
            //AutoSeededRandomPool prng;
            
            //SecByteBlock key(DES_EDE3::DEFAULT_KEYLENGTH);
            //prng.GenerateBlock( key, key.size() );
            
            //Set counter to 0
            //unsigned char ctr[ DES_EDE3::BLOCKSIZE ] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; // ctr = counter - Set starting value to 0 in hex.
            
            
            //Run Generation.cpp
            
            // unsigned char ctr[ DES_EDE3::BLOCKSIZE ]; // ctr = counter - Set starting value to 0 in hex.
            //prng.GenerateBlock( ctr, sizeof(ctr) ); // Generate starting value for counter
            
            //memset(&ctr, 0, sizeof(ctr)); // Set all values to 0
            
            
            //WHY DONT YOU MAKE IT COUNT YOURSELF USING INT YOU DIV!!!
            
            cout << "Running GEN Script" << endl;
            
            // Declare Generator
            GENERATOR firstGen;
            
            //Reset Counter for Generator
            firstGen.resetCtrEasy();
            
            cout << "When the counter reaches main, it is of size: " << firstGen.getCtr().size() << endl;
            
            //Initialize the key
            firstGen.initialiseKey();
            
            cout << "The starting key is: " << firstGen.getKeyString() << endl;
            
            //Run the generator 10 times.
            for (int i = 0; i < 10; i++) {
                
                string Generated = firstGen.GEN();
            }
            
            
            //CHANGE THE MOTHERFUCKING KEYYYYYYYYY
            
            
//            //Create temp variable for new key
//            string replaceKey = "";
//            
//            
//            //Run the generator until the length produced is less than the required length for the key
//            while (replaceKey.length() < 24) {
//                
//                replaceKey += firstGen.GEN();
//            }
//            
//            cout << "Key length is currently: " << replaceKey.length() << endl;
//            
//            //If statement - If the length is now higher, calculates the number of characters over and removes them
//            if (replaceKey.length() > 24) {
//                int ExtraLength = replaceKey.length() - 24;
//                cout << "Extra Length: " << ExtraLength << endl;
//                
//                replaceKey.erase(replaceKey.end() - ExtraLength, replaceKey.end());
//                
//            }
//            
//            cout << "key Length is now: " << replaceKey.length() << endl;
//            
//            // Replace the key
//            firstGen.setKey(replaceKey);
//            
//            cout << "Successfully changed the key!" << endl;
//            
//
            cout << "The old key is: " << firstGen.getKeyString() << endl;
            
            changeKey(firstGen);
            
            cout << "The New Key is: " << firstGen.getKeyString() << endl;
            
            //END CHANGING THE MOTHERFUCKING KEYYYYY
            
            //Run generator with new key
            
            for (int i = 0; i < 10; i++) {
                string Generated = firstGen.GEN();
            }
            
            changeKey(firstGen);
            
            break;
            
    }
    
    cout << "Your the fucking boss, it works mother fucker!" << endl;
    
    return 0;
}