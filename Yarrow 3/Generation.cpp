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
    
    cout << endl;
    //cout << "KeyString = " << keyString << endl;
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
    
    cout << "The generated counter is of size: " << ctr.size() << endl;
    
    cout << "But using sizeof(), we return: " << sizeof(ctr) << endl;
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
    
    //cout << "Key String is : " << keyString << endl << "Length: " << keyString.size() << endl;
    
    //Convert string for new key into SecByteBlock and set as new key
    SecByteBlock replacementKey(DES_EDE3::KEYLENGTH);
    
    string keyString;
    
    StringSource(keyStringHex, true, new CryptoPP::HexDecoder(new CryptoPP::StringSink( keyString)));
    
    
    // keyString.size()/2 as hex information held as string will require double the system memory
    size_t s = STDMIN(replacementKey.size(),keyString.size());
    
    //cout << " s = " << s << endl;
    
    memcpy(replacementKey.data(),keyString.data(),s);
    
    if (s<DES_EDE3::KEYLENGTH) {
        memset(replacementKey.data() + s, 0, DES_EDE3::KEYLENGTH - s);
    }
    //replacementKey= SecByteBlock(reinterpret_cast<const byte*>(keyString.data()), keyString.size());
//    
//    unsigned char x[24];
//    
//    stringstream sst;
//    
//    
//    for (int i = 0; i < keyString.size()/2; i ++ ) {
//        
//        sst << hex << keyString.substr(2*i,3);
//        sst >> x[i];
//    
//        cout << "x is: " << x;
//    }
    
   // HKDF<SHA256> kdf;
    
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
        
   //     cout << "vTemp: " << vTemp << endl;
        
        StringSource(vTemp, true, new CryptoPP::HashFilter(sha1,new CryptoPP::StringSink(vPrev)));
        vTemp = "";
        
    }
    
    //Set last vi to vPt for use later
    string vPt = vPrev;
    
   // cout << "vPt = " << vPt << endl;
    
    
    //     STEP 3     //
    
    //first convert key to string
    string keyString = string(reinterpret_cast<const char*>(key.data()),key.size());
    
    //Set vTemp to input for h' formula
    vTemp = vPt + keyString;
    
    // Declare empty variable for s0
    string s0 = "";
    
    //Hash vPt and the key to produce m, the value of s0
    StringSource(vTemp, true, new CryptoPP::HashFilter(sha1,new CryptoPP::StringSink(s0)));
    
   // cout << "s0 size: " << s0.size() << endl;
    
    // Declare empty variable for si values
    string sInput = s0;
    string si = "";
    
    
    //While loop to ca;lculate varions si values by hashing all of those previously hashed.
    while (sInput.size() < DES_EDE3::KEYLENGTH) {
        
        StringSource(sInput, true, new CryptoPP::HashFilter(sha1,new CryptoPP::StringSink(si)));
        //cout << "si size: " << si.size() << endl;
        sInput = sInput + si;
        si = "";
        //cout << endl << sInput.size() << endl;
        
    }
    //cout << endl << sInput.size() << endl << DES_EDE3::KEYLENGTH << endl;
    
    //If loop to cut down sInput to the length required for the new key
    if (sInput.size() > DES_EDE3::KEYLENGTH) {
        sInput.erase (DES_EDE3::KEYLENGTH,sInput.size() - DES_EDE3::KEYLENGTH);
    }
    
   // cout << "sInput size = " << sInput.size() << endl;
    
    
    // THE FOLLOWING THREE LINES OF CODE ARE FOR CHECKING - NOTE sInputHex IS NOT USED APART FROM PRINTING TO SCREEN ///
    string sInputHex;
    
    StringSource(sInput,true,new CryptoPP::HexEncoder(new CryptoPP::StringSink(sInputHex)));
    
    //cout << "sInput in hex: " << sInputHex << endl;
    
    // cout << v0 << endl;
    
    //  FOLLOWING CODE COPIED FROM SET KEY FROM STRING - Have removed conversion from Hex as key is already in byte form //////
    
    
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
    
    //AutoSeededRandomPool prng;
    //
    //SecByteBlock key(DES_EDE3::DEFAULT_KEYLENGTH);
    // prng.GenerateBlock( key, key.size() );
    
    //Assign variables for counter and key from class
    CryptoPP::SecByteBlock key = newKey;
    //vector <unsigned char> ctrVec = newCtr;
    
    
    //Convert new int ctr to binary
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
    
    
    
    // cout << "Upon reaching the Generator Function the counter is of size: " << ctrVec.size() << endl;
    
    //Declare variable for non-vector type counter
    //unsigned char ctr[ctrVec.size()];
    
    cout << endl << "The array is of size before filling: " << sizeof(ctr) << endl;
    
    //Declare temperary variable for use in loop
    //unsigned char tempCtr;
    
    //Run for loop to convert vector to array using pointers [FUCKING SCRAY MATE]
    //for(int i = 0; i < ctrVec.size(); i++) {
    
    //Get value for individaul vector
    //     tempCtr = ctrVec[i];
    
    //Push back into array
    //       ctr[i] = tempCtr;
    // }
    
    cout << "Key size: " << key.size() << endl;
    
    cout << "Counter size: " << sizeof(ctr) << endl;
    
    
    // Convert newCtr1 to binary representation in 8 bit as a string for use within the algorithm
    string plain = bitset<8>(newCtr1).to_string();
    //string plain = "Hello";
    string cipher, encoded, recovered;
    
    //cout << "Please enter a message to be Cipered" << endl;
    //cin >> plain;
    //cout << endl;
    
    /*********************************\
     Pad the message
     \*********************************/
    
    try
    {
        cout << "plain text: " << plain << endl;
        
        CTR_Mode< DES_EDE3 >::Encryption e;
        e.SetKeyWithIV( key, key.size(), ctr );
        
        // The StreamTransformationFilter adds padding
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher. CTR does not.
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
    
    // Pretty print cipher text
    StringSource ss2( cipher, true,
                     new HexEncoder(
                                    new StringSink( encoded )
                                    ) // HexEncoder
                     ); // StringSource
    cout << "cipher text: " << encoded << endl;
    
    /*********************************\
     Decode the Message
     \*********************************/
    //
    //    try
    //    {
    //        CTR_Mode< DES_EDE3 >::Decryption d;
    //        d.SetKeyWithIV( key, key.size(), ctr );
    //
    //        // The StreamTransformationFilter removes
    //        //  padding as required.
    //        StringSource ss3( cipher, true,
    //                         new StreamTransformationFilter( d,
    //                                                        new StringSink( recovered )
    //                                                        ) // StreamTransformationFilter
    //                         ); // StringSource
    //
    //        cout << "recovered text: " << recovered << endl;
    //    }
    //    catch( CryptoPP::Exception& e )
    //    {
    //        cerr << e.what() << endl;
    //        exit(1);
    //    }
    
    
    //Increase the counter by one
    newCtr1 = newCtr1 + 1;
    
    
    return encoded;
}
