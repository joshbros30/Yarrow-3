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
    
    HexEncoder hex(new StringSink(keyString));
    hex.Put(key.data(),key.size());
    hex.MessageEnd();
    
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

int GENERATOR::resetCtrEasy() {
    newCtr1 = 0;
    
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

SecByteBlock GENERATOR::setKey(string keyString){
    
    //Convert string for new key into SecByteBlock and set as new key
    SecByteBlock replacementKey(reinterpret_cast<const byte*>(keyString.data()), keyString.size());
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
    
    //cout << ctr[1] << endl; // Output Random Value.
    string plain = "Hello";
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
    
    
    newCtr1 = newCtr1 + 1;
    
    
    return encoded;
}

//int DES1::DES() {
//
//
//    AutoSeededRandomPool prng;
//
//    SecByteBlock key(DES_EDE3::DEFAULT_KEYLENGTH);
//    prng.GenerateBlock( key, key.size() );
//
//    byte ctr[ DES_EDE3::BLOCKSIZE ];
//    prng.GenerateBlock( ctr, sizeof(ctr) );
//
//
//    /*********************************\
//     \*********************************/
//
//
////
////    AutoSeededRandomPool prng;
////
////    SecByteBlock key(0x00, DES_EDE3::DEFAULT_KEYLENGTH);
////    prng.GenerateBlock(key, key.size());
////
////    cout << key.size() << endl;
////
////    byte iv[DES_EDE3::BLOCKSIZE];
////    prng.GenerateBlock(iv, sizeof(iv));
//
//    string plain;
//    string cipher, encoded, recovered;
//
//    cout << "Please enter a message to place through DES Counter Mode" << endl;
//
//    cin >> plain;
//
//    cout << endl;
//
//    /*********************************\
//     \*********************************/
//
//    try
//    {
//        cout << "plain text: " << plain << endl;
//
//        CTR_Mode< DES_EDE3 >::Encryption e;
//        e.SetKeyWithIV(key, key.size(), iv);
//
//        // The StreamTransformationFilter adds padding
//        //  as required. ECB and CBC Mode must be padded
//        //  to the block size of the cipher.
//        StringSource ss1(plain, true,
//                         new StreamTransformationFilter(e,
//                                                        new StringSink(cipher)
//                                                        ) // StreamTransformationFilter
//                         ); // StringSource
//    }
//    catch(const CryptoPP::Exception& e)
//    {
//        cerr << e.what() << endl;
//        exit(1);
//    }
//
//    /*********************************\
//     \*********************************/
//
//    // Pretty print
//    StringSource ss2(cipher, true,
//                     new HexEncoder(
//                                    new StringSink(encoded)
//                                    ) // HexEncoder
//                     ); // StringSource
//
//    cout << "cipher text: " << encoded << endl;
//
//    /*********************************\
//     \*********************************/
//
//    try
//    {
//        CTR_Mode< DES_EDE3 >::Decryption d;
//        d.SetKeyWithIV(key, key.size(), iv);
//
//        // The StreamTransformationFilter removes
//        //  padding as required.
//        StringSource ss3(cipher, true,
//                         new StreamTransformationFilter(d,
//                                                        new StringSink(recovered)
//                                                        ) // StreamTransformationFilter
//                         ); // StringSource
//
//        cout << "recovered text: " << recovered << endl;
//    }
//    catch(const CryptoPP::Exception& e)
//    {
//        cerr << e.what() << endl;
//        exit(1);
//    }
//    return 0;
//}

