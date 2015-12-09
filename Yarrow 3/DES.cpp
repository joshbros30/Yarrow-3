//
//  DES.cpp
//  Security Test
//
//  Created by Home on 17/11/2015.
//  Copyright © 2015 Home. All rights reserved.
//

#include "DES.hpp"



using namespace CryptoPP;

using namespace std;


int DES1::DES() {
    
    AutoSeededRandomPool prng;
    
    SecByteBlock key(DES_EDE3::DEFAULT_KEYLENGTH);
    prng.GenerateBlock( key, key.size() );
    
    cout << "Key size: " << key.size() << endl;
    
    byte ctr[ DES_EDE3::BLOCKSIZE ] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; // ctr = counter - Set starting value to 0 in hex.
    //prng.GenerateBlock( ctr, sizeof(ctr) ); // Generate starting value for counter
    
    cout << "Counter size: " << sizeof(ctr) << endl;
    
    cout << ctr << endl; // Output Random Value.
    string plain;
    string cipher, encoded, recovered;
    
    cout << "Please enter a message to be Cipered" << endl;
    cin >> plain;
    cout << endl;
    
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
    
    try
    {
        CTR_Mode< DES_EDE3 >::Decryption d;
        d.SetKeyWithIV( key, key.size(), ctr );
        
        // The StreamTransformationFilter removes
        //  padding as required.
        StringSource ss3( cipher, true, 
                         new StreamTransformationFilter( d,
                                                        new StringSink( recovered )
                                                        ) // StreamTransformationFilter
                         ); // StringSource
        
        cout << "recovered text: " << recovered << endl;
    }
    catch( CryptoPP::Exception& e )
    {
        cerr << e.what() << endl;
        exit(1);
    }
    
    
    
    
    
    return 0;
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
