#include <iostream>
#include <fstream>
#include "codec.h"

int main(int argc, char *argv[]){
    
    //The mode will be -c, -d, or -bwt
    std::string mode = argv[1];
    
    if(argc == 4){ 
    
        if(mode == "-c"){
            codec::encoder(argv[2], argv[3]);
        }else if(mode == "-d"){
            codec::decoder(argv[2], argv[3]);
        }else{
            std::__throw_runtime_error("Invalid mode: Try -c for compression, -d for decompression, or -bwt for strictly use of the bwt function");
        }
    }else if(argc == 2){
        if(mode == "-bwt"){
            std::string input;
            std::cout << "Please type in any input for the BWT function: " << std::endl;
            cin >> input;
            BWT transform;
            std::string BWTinput = transform.bwt(input);
            std::cout << "The BWT version of your input: " << std::endl << BWTinput << std::endl;
            std::string BWToutput = transform.ibwt(BWTinput);
            std::cout << "The IBWT version of your input: " << std::endl << BWToutput << std::endl;

        }
    }
    return 0;

}
