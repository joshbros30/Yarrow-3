////
////  ReseedMech.cpp
////  Yarrow 3
////
////  Created by Home on 22/12/2015.
////  Copyright © 2015 Home. All rights reserved.
////
//
//#include "ReseedMech.hpp"
//
//int RESEEDER::RESEEDTest() {
//    
//    
//    //            STEP 1 & 2         //
//    
//    
//    //Declare ifstream to allow file to be read and string to store file lines
//    ifstream fast("/fastPoolTest.txt");
//    string line;
//    
//    // if-else statement to test the file has been opened
//    if (! fast.is_open()) {
//        cout << "The Fast Pool was failed to be found!" << endl;
//        return 9;
//    } else {
//        cout << "The Fast Pool was successfully located!" << endl;
//        
//        // use getline to read single line of fast file
//        getline (fast,line);
//        
//        //close the file now data has been read
//        fast.close();
//        
//    }
//    
//     int Pt = 10;
//    // Declare instance of SEC1 and produce a hash of fast pool
//    SEC1 h;
//    string vPt = h.SHAV(line,Pt);
//    
//    //Print the output of the hashing function
//    //ERRORcout << "The hash of Fast Pool is: " << v0 << endl;
//    
//    //            STEP 2           //
//    
//    // Pt SET TO TEN FOR NO REASON WHATSOEVER - CANNOT FIND DEFINITION OF VALUE FOR Pt //
//    
//   
//    
//    vector<string> v;
//    
//    // push back initialisation vector
//   //ERROR v.push_back(v0);
//    
//    //For loop to produce iterative vi formula and push them back onto v vector
//    for (int i = 1; i <= Pt; i++) {
//        
//        //Define temp string and null it
//        string vTemp = "";
//        
//        cout << "Input string is: " << v[i-1] + v[0] + to_string(i) << endl;
//        
//        // Produce hash of iterative formula
//     //ERROR   vTemp = h.SHA(v[i-1] + v[0] + to_string(i));
//        
//        cout << "vTemp is: " << vTemp << endl;
//        
//        //push back onto v vector
//        v.push_back(vTemp);
//    }
//    
//    
//    //            STEP 3           //
//    
//    int keySize = 24;
//    
//   //ERROR string s = h.SHA(v[Pt]);// + key);
//    string sTemp;
// //ERROR   while (s.length() / 2 < keySize) {
// //ERROR       sTemp = h.SHA(s);
//        cout << "While loop is running." << endl;
//    //ERROR    s = s + sTemp;
//    }
//    
//    
//    
//    
//    return 0;
//}