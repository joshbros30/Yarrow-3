//
//
//#include "SHA.hpp"
//
//string SEC1::SHAV(string message, int Pt){
//    
//    //          STEP 1          //
//    
//    // Declare SHA1 Variables and convert input mesage to unsighed char[]
//    
//    unsigned char *ibuf=new unsigned char[message.length()+1];
//    strcpy((char *)ibuf,message.c_str());
//    
//    unsigned char obuf[20];
//    
//    unsigned char test[10000];
//    
//    // Calculate the size of the input message
//    size_t s = strlen((char*)ibuf);
//    
//    // Do the SHA1 hashing algorithm for original input v0
//    SHA1(ibuf, s, obuf);
//    
//    //Set new input buffer to output for v0
//    unsigned char *v0 = new unsigned char[strlen((char*)obuf)];
//    unsigned char *vPrev = new unsigned char[strlen((char*)obuf)];
//    vPrev = obuf;
//    v0 = obuf;
//    //ibuf = obuf;
//    
//    
//    for (int i = 0; i < Pt; i++) {
//        strcat(test,
//        
//    }
//    
//    
////    //Print the hashing output
////    for (int i = 0; i < 20; i++) {
////        
////        printf("%02x ", obuf[i]);
////    }
////    
////    //Add a new line for clarity
////    printf("\n");
////    
////    //convert to string for return
////    
////    stringstream ss;
////    ss << hex << setfill('0');
////    
////    for (int i = 0; i < 20; i++) {
////        //ss << "%02x" << (int)obuf[i];
////        ss << setw(2) << static_cast<unsigned>(obuf[i]);
////    }
////    string output = ss.str();
//    
//    return output;
//    
//
//}
//
//string SEC1::SHAString(string message) {
//    
//
//    
//    // Declare SHA1 Variables and convert input mesage to unsighed char[]
//    
//    unsigned char *ibuf=new unsigned char[message.length()+1];
//    strcpy((char *)ibuf,message.c_str());
//    
//    unsigned char obuf[20];
//    
//    // Calculate the size of the input message
//    size_t s = strlen((char*)ibuf);
//    
//    // Do the SHA1 hashing algorithm
//    SHA1(ibuf, s, obuf);
//    
//    //Print the hashing output
//    for (int i = 0; i < 20; i++) {
//        
//        printf("%02x ", obuf[i]);
//    }
//    
//    //Add a new line for clarity
//    printf("\n");
//    
//    //convert to string for return
//    
//    stringstream ss;
//    ss << hex << setfill('0');
//    
//    for (int i = 0; i < 20; i++) {
//        //ss << "%02x" << (int)obuf[i];
//        ss << setw(2) << static_cast<unsigned>(obuf[i]);
//    }
//    string output = ss.str();
//
//    return output;
//    
//}
//
//string SEC1::SHAChar(unsigned char ibuf[] ) {
//    
//    
//    unsigned char obuf[20];
//    
//    // Calculate the size of the input message
//    size_t s = strlen((char*)ibuf);
//    
//    // Do the SHA1 hashing algorithm
//    SHA1(ibuf, s, obuf);
//    
//    //Print the hashing output
//    for (int i = 0; i < 20; i++) {
//        
//        printf("%02x ", obuf[i]);
//    }
//    
//    //Add a new line for clarity
//    printf("\n");
//    
//    //convert to string for return
//    
//    stringstream ss;
//    ss << hex << setfill('0');
//    
//    for (int i = 0; i < 20; i++) {
//        //ss << "%02x" << (int)obuf[i];
//        ss << setw(2) << static_cast<unsigned>(obuf[i]);
//    }
//    string output = ss.str();
//    
//    return output;
//    
//}
//
//
//
//int SEC1::SHATEST()
//{
//    
//    /* Initialise String and Take in input for initial message.
//     
//     CURRENT DOES NOT ACCEPT SPACES - NEEDS WORKING
//     */
//    string message;
//    cout << "Please enter message for hashing" << endl;
//    cin >> message;
//    
//    cout << "Your message is of length: " << message.length() << endl;
//    
//    
//    // Declare SHA1 Variables and convert mesage to unsighed char[]
//    
//    unsigned char *ibuf=new unsigned char[message.length()+1];
//    strcpy((char *)ibuf,message.c_str());
//    
//    unsigned char obuf[20];
//    
//    // Calculate the size of the input message
//    size_t s = strlen((char*)ibuf);
//    
//    // Do the SHA1 hashing algorithm
//    SHA1(ibuf, s, obuf);
//    
//    
//    
//    //Print the hashing output
//    for (int i = 0; i < 20; i++) {
//        
//        printf("%02x", obuf[i]);
//        
//    }
//    
//    //Add a new line for clarity
//    printf("\n");
//    
//    //Convert to base64
//    
//    
//    
//    return 0;
//}
//
