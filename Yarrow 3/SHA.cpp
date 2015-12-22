

#include "SHA.hpp"

string SEC1::SHA(string message) {
    

    
    // Declare SHA1 Variables and convert input mesage to unsighed char[]
    
    unsigned char *ibuf=new unsigned char[message.length()+1];
    strcpy((char *)ibuf,message.c_str());
    
    unsigned char obuf[20];
    
    // Calculate the size of the input message
    size_t s = strlen((char*)ibuf);
    
    // Do the SHA1 hashing algorithm
    SHA1(ibuf, s, obuf);
    
    //Print the hashing output
    for (int i = 0; i < 20; i++) {
        
        printf("%02x ", obuf[i]);
    }
    
    //Add a new line for clarity
    printf("\n");
    
    //convert to string for return
    
    stringstream ss;
    
    for (int i = 0; i < 20; i++) {
        ss << hex << (int)obuf[i];
        
    }
    string output = ss.str();

    return output;
    
}


int SEC1::SHATEST()
{
    
    /* Initialise String and Take in input for initial message.
     
     CURRENT DOES NOT ACCEPT SPACES - NEEDS WORKING
     */
    string message;
    cout << "Please enter message for hashing" << endl;
    cin >> message;
    
    cout << "Your message is of length: " << message.length() << endl;
    
    
    // Declare SHA1 Variables and convert mesage to unsighed char[]
    
    unsigned char *ibuf=new unsigned char[message.length()+1];
    strcpy((char *)ibuf,message.c_str());
    
    unsigned char obuf[20];
    
    // Calculate the size of the input message
    size_t s = strlen((char*)ibuf);
    
    // Do the SHA1 hashing algorithm
    SHA1(ibuf, s, obuf);
    
    //Print the hashing output
    for (int i = 0; i < 40; i++) {
        
        printf("%02x ", obuf[i]);
    }
    
    //Add a new line for clarity
    printf("\n");
    
    return 0;
}

