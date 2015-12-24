//
//  SHA.h
//  Security Test
//
//  Created by Home on 12/11/2015.
//  Copyright © 2015 Home. All rights reserved.
//


#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>


using namespace std;

#ifndef SHA_h
#define SHA_h

class SEC1 {
public:
    int SHATEST();
    string SHAString(string);
    string SHAChar(unsigned char[]);
    string SHAV(string,int);
};



#endif /* SHA_h */
