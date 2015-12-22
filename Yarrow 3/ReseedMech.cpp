//
//  ReseedMech.cpp
//  Yarrow 3
//
//  Created by Home on 22/12/2015.
//  Copyright © 2015 Home. All rights reserved.
//

#include "ReseedMech.hpp"

int RESEEDER::RESEED() {
    
    
    //            STEP 1           //
    
    
    //Declare ifstream to allow file to be read and string to store file lines
    ifstream fast("/fastPoolTest.txt");
    string line;
    
    // if-else statement to test the file has been opened
    if (! fast.is_open()) {
        cout << "The Fast Pool was failed to be found!" << endl;
        return 9;
    } else {
        cout << "The Fast Pool was successfully located!" << endl;
        
        // use getline to read single line of fast file
        getline (fast,line);
        
        //close the file now data has been read
        fast.close();
        
    }
    
    // Declare instance of SEC1 and produce a hash of fast pool
    SEC1 hey;
    string hash = hey.SHA(line);
    
    //Print the output of the hashing function
    cout << "The hash of Fast Pool is: " << hash << endl;
    
    //            STEP 2           //
    
    
    
    
    return 0;
}