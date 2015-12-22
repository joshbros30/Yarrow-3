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
#include <iostream>
#include <sstream>
#include <iomanip>


using namespace std;

#ifndef SHA_h
#define SHA_h

class SEC1 {
public:
    int SHATEST();
    string SHA(string);
};



#endif /* SHA_h */
