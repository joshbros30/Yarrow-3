//
//  SHANew.hpp
//  Yarrow 3
//
//  Created by Home on 23/12/2015.
//  Copyright © 2015 Home. All rights reserved.
//

#ifndef SHANew_hpp
#define SHANew_hpp

#include <stdio.h>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include "cryptopp/des.h"

#include <string>
#include <iostream>

using namespace std;
using namespace CryptoPP;

class SHANew {
public:
    string SHA1(string, int,SecByteBlock);
};


#endif /* SHANew_hpp */
