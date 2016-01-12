//
//  Generation.cpp
//  Yarrow 3
//
//  Created by Home on 08/12/2015.
//  Copyright © 2015 Home. All rights reserved.
//

#include "Generation.hpp"

using namespace std;
using namespace CryptoPP;

//Default Constructor Definition
GENERATOR::GENERATOR(){
    newCtr1 = 0;
}

//Overload Constructor Definition
GENERATOR::GENERATOR(vector <unsigned char> ctr,SecByteBlock key) {
    newCtr = ctr;
    newKey = key;
}



// Accessor Function for key
SecByteBlock GENERATOR::getKey() const {
    return newKey;
}

string GENERATOR::getKeyString() {
    
    SecByteBlock key = newKey;
    string keyString = string(reinterpret_cast<const char*>(key.data()),key.size());
    
    cout << "PreHex: " << keyString << endl << "Post Hex: ";
    
    //Blank key string as strink sink appends, doesnt replace
    keyString = "";
    HexEncoder hex(new StringSink(keyString));
    hex.Put(key.data(),key.size());
    hex.MessageEnd();

    return keyString;
    
}

//Accessor Function for ctr
vector <unsigned char> GENERATOR::getCtr() const {
    return newCtr;
}



//Reset ctr function.
vector <unsigned char> GENERATOR::resetCtr() {
    
    vector <unsigned char> ctr;
    
    for (int i = 0; i < 8; i++) {
        ctr.push_back(0);
    }
    
    return newCtr = ctr;
}

int64_t GENERATOR::resetCtrEasy() {
    newCtr1 = 0;
    
    return newCtr1;
}

int64_t GENERATOR::setCtr(int64_t counter) {
    newCtr1 = counter;
    
    return newCtr1;
}



// Generate Initial Key using Random Pool
//OBVIOUSLY THE RANDOM POOL IS WRONG - THIS WILL NEED SORTING!

CryptoPP::SecByteBlock GENERATOR::initialiseKey() {
    AutoSeededRandomPool prng;
    
    SecByteBlock key(DES_EDE3::DEFAULT_KEYLENGTH);
    prng.GenerateBlock( key, key.size() );
    return newKey = key;
}

SecByteBlock GENERATOR::setKey(const string keyStringHex){
    
    //Convert string for new key into SecByteBlock and set as new key
    SecByteBlock replacementKey(DES_EDE3::KEYLENGTH);
    
    string keyString;
    
    StringSource(keyStringHex, true, new CryptoPP::HexDecoder(new CryptoPP::StringSink( keyString)));
    
    
    // keyString.size()/2 as hex information held as string will require double the system memory
    size_t s = STDMIN(replacementKey.size(),keyString.size());
    
    memcpy(replacementKey.data(),keyString.data(),s);
    
    if (s<DES_EDE3::KEYLENGTH) {
        memset(replacementKey.data() + s, 0, DES_EDE3::KEYLENGTH - s);
    }

    return newKey = replacementKey;
    
}


SecByteBlock GENERATOR::reseedStep1(int Pt){
    
    //Define Sha1 Hashfilter
    CryptoPP::SHA1 sha1;
    
    //Define key as generators key
    SecByteBlock key = newKey;
    
    
    //Declare ifstream to allow file to be read and string to store file lines
        ifstream fast("/fastPoolTest.txt");
        string line;
    
        // if-else statement to test the file has been opened
        if (! fast.is_open()) {
            cout << "The Fast Pool was failed to be found!" << endl;
            abort();
        } else {
            cout << "The Fast Pool was successfully located!" << endl;
    
            // use getline to read single line of fast file
            getline (fast,line);
    
            //close the file now data has been read
            fast.close();
            
        }
        

    
    
    //      STEP 1       //
    
    //Set v0 to empty string
    string v0 = "";
    
    //Hash input data and assign it to string V0 in Hex
    StringSource(line, true, new CryptoPP::HashFilter(sha1, /*new CryptoPP::HexEncoder*/(new CryptoPP::StringSink(v0))));
    
    
    
    //    STEP 2         //
    
    // Now run iterative formula for vi
    
    //Declare variables for hash function
    string vPrev;
    string vTemp = "";
    
    
    //For loop - First produce input for hash, then hash to produce vi each time.
    for (int i = 1; i <= Pt;i++) {
        vTemp = vPrev + v0 + to_string(i);
        
        StringSource(vTemp, true, new CryptoPP::HashFilter(sha1,new CryptoPP::StringSink(vPrev)));
        vTemp = "";
        
    }
    
    //Set last vi to vPt for use later
    string vPt = vPrev;
    
    
    //     STEP 3     //
    
    //first convert key to string
    string keyString = string(reinterpret_cast<const char*>(key.data()),key.size());
    
    //Set vTemp to input for h' formula
    vTemp = vPt + keyString;
    
    // Declare empty variable for s0
    string s0 = "";
    
    //Hash vPt and the key to produce m, the value of s0
    StringSource(vTemp, true, new CryptoPP::HashFilter(sha1,new CryptoPP::StringSink(s0)));
    
    // Declare empty variable for si values
    string sInput = s0;
    string si = "";
    
    
    //While loop to ca;lculate varios si values by hashing all of those previously hashed.
    while (sInput.size() < DES_EDE3::KEYLENGTH) {
        
        StringSource(sInput, true, new CryptoPP::HashFilter(sha1,new CryptoPP::StringSink(si)));
        sInput = sInput + si;
        si = "";
        
    }
    
    //If loop to cut down sInput to the length required for the new key
    if (sInput.size() > DES_EDE3::KEYLENGTH) {
        sInput.erase (DES_EDE3::KEYLENGTH,sInput.size() - DES_EDE3::KEYLENGTH);
    }
    
    string sInputHex;
    
    StringSource(sInput,true,new CryptoPP::HexEncoder(new CryptoPP::StringSink(sInputHex)));
    
    
    //Convert string for new key into SecByteBlock and set as new key
    SecByteBlock replacementKey(DES_EDE3::KEYLENGTH);
    
    size_t s = STDMIN(replacementKey.size(),sInput.size());
    
    memcpy(replacementKey.data(),sInput.data(),s);
    
    if (s<DES_EDE3::KEYLENGTH) {
        memset(replacementKey.data() + s, 0, DES_EDE3::KEYLENGTH - s);
    }

    
    return newKey = replacementKey;
    
}

string GENERATOR::GEN() {
    
    
    //Assign variables for counter and key from class
    CryptoPP::SecByteBlock key = newKey;
    
    //Convert int newCtr1 to binary
    int rem,i, a = newCtr1;
    
    unsigned char ctr[8];
    
    for (i = 0; i < 8; i++) {
        if (a == 0) {
            ctr[i]= '0';
        }
        else {
            rem = a % 2;
            
            if (rem == 0){
                ctr[i] = '0';
            }
            else {
                ctr[i] = '1';
            }
            a = a/2;
        }
        
    }
    
    
    // Convert newCtr1 to binary representation in 8 bit as a string for use within the algorithm
    string plain = bitset<8>(newCtr1).to_string();
    string cipher, encoded, recovered;
    
    
    /*********************************\
     Pad the message
     \*********************************/
    
    try
    {
        cout << "plain text: " << plain << endl;
        
        CTR_Mode< DES_EDE3 >::Encryption e;
        e.SetKeyWithIV( key, key.size(), ctr );
        
        StringSource ss1( plain, true,
                         new StreamTransformationFilter( e,
                                                        new StringSink( cipher )
                                                        ) // StreamTransformationFilter
                         ); // StringSource
    }
    catch( CryptoPP::Exception& e )
    {
        cerr << e.what() << endl;
        exit(1);
    }
    
    /*********************************\
     Encode the Message
    \*********************************/
    
    // print cipher text
    StringSource ss2( cipher, true,
                     new HexEncoder(
                                    new StringSink( encoded )
                                    ) // HexEncoder
                     ); // StringSource
    cout << "cipher text: " << encoded << endl;
    
    //Increase the counter by one
    newCtr1 = newCtr1 + 1;
    
    
    return encoded;
}
