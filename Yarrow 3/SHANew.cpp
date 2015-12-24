//
//  SHANew.cpp
//  Yarrow 3
//
//  Created by Home on 23/12/2015.
//  Copyright © 2015 Home. All rights reserved.
//

#include "SHANew.hpp"


 string SHANew::SHA1(string message, int Pt, SecByteBlock key) {
     
     //Define Sha1 Hashfilter
     CryptoPP::SHA1 sha1;
     
     
     //      STEP 1       //
     
     //Set v0 to empty string
     string v0 = "";
     
     //Hash input data and assign it to string V0 in Hex
     StringSource(message, true, new CryptoPP::HashFilter(sha1, /*new CryptoPP::HexEncoder*/(new CryptoPP::StringSink(v0))));
     
     
     
     
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
     string si = s0;
     
     
     //While loop to ca;lculate varions si values by hashing all of those previously hashed.
     while (sInput.size() < DES_EDE3::KEYLENGTH) {
         
         StringSource(sInput, true, new CryptoPP::HashFilter(sha1,new CryptoPP::StringSink(si)));
         sInput = sInput + si;
         
     }
     
     //If loop to cut down sInput to the length required for the new key
     if (sInput.size() > DES_EDE3::KEYLENGTH) {
         sInput.erase (DES_EDE3::KEYLENGTH,sInput.size() - DES_EDE3::KEYLENGTH);
     }
     
     
     
    // cout << v0 << endl;
     
     return v0;
 }