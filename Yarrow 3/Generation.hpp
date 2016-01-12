//
//  Generation.hpp
//  Yarrow 3
//
//  Created by Home on 08/12/2015.
//  Copyright © 2015 Home. All rights reserved.
//

#ifndef Generation_hpp
#define Generation_hpp

#include <stdio.h>
#include <stdio.h>
#include <cryptopp/cryptlib.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <bitset>
#include <fstream>

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include "cryptopp/cryptlib.h"
using CryptoPP::Exception;

#include "cryptopp/hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "cryptopp/filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "cryptopp/des.h"
using CryptoPP::DES_EDE3;

#include "cryptopp/modes.h"
using CryptoPP::CTR_Mode;

#include "cryptopp/secblock.h"
using CryptoPP::SecByteBlock;


using namespace std;


class GENERATOR {
public:
    //Default Constructor
   GENERATOR();
    
    //Overload Constructor
    GENERATOR(vector <unsigned char>,SecByteBlock);
    
    //Acessor Functions
    SecByteBlock getKey() const;
    
    vector <unsigned char> getCtr() const;
    
    string getKeyString();
    
    //Reset Counter
    vector <unsigned char> resetCtr();
    
    //Initilise Key
    CryptoPP::SecByteBlock initialiseKey();
    
    //SetKey
    
    CryptoPP::SecByteBlock setKey(string);
    
    
    //Generator Function
    string GEN();
    
    //Reseed Mechanism
    CryptoPP::SecByteBlock reseedStep1(int);
    
    
    //Reset the counter the sensible way
    int64_t resetCtrEasy();
    
    int64_t setCtr(int64_t);
    
    
    
private:
    //Hold the key
    SecByteBlock newKey;
    //Hold the counter
    vector <unsigned char> newCtr;
    
    //Hold the counter in a much more sensible way
    int64_t newCtr1;
    

};

#endif /* Generation_hpp */
