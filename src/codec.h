#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include "huffTree.h"
#include "freqCount.h"


//The encoder combines both bwt and huffman to introduce a more optimized compression
class codec{
    public:
        //Encoder takes the bwt string stream and converts it into a huffman encoded stream
        //  which allows for a better optimized compression
        void static encoder(std::string fileName, std::string outputFile);

        //Decoder takes the huffman encoded bwt strings and re builds the huffman tree, 
        //  and then takes the bwt strings and applies ibwt to convert back to normal.
        void static decoder(std::string fileName, std::string outputFile);
};

void codec::encoder(std::string filename, std::string outputFile){
    
    //Open input text file and dump its values into a stringstream
    std::ifstream input(filename);
    std::string inputString;
    std::stringstream buffer;
    if(input.is_open()){
        buffer << input.rdbuf();
        input.close();
    }


    //Call bwt on the inputString data
    BWT transform;
    std::string transformedString;
    
    while(std::getline(buffer, inputString, '\n')){
        transformedString += transform.bwt(inputString);
        transformedString += '\n';
    }

    //Count the frequency of the values on the data (used in compression part)
    freqCount *newFc = new freqCount;
    newFc->countFile(transformedString);

    //Create priority queue as needed in Huffman compression
    std::priority_queue<huffObj, vector<huffObj>, Compare> newQueue;
    int objArrLen = newFc->totChar; 
    huffObj objArr[objArrLen];
    int objIndex = 0;

    //Create a node for each ASCII character
    for(int i = 0; i < 256; i++){
        if(newFc->freqArr[i] > 0){
            huffNode *newNode = new huffNode(i, newFc->freqArr[i], NULL, NULL, NULL);
            objArr[objIndex++].node = newNode;
        }
    }

    //Push the nodes to the priority queue
    for(int i = 0; i < objArrLen; i++){
        newQueue.push(objArr[i]);
    }

    //Build binary tree for huffman
    huffTree* newHT = new huffTree();
    newHT->buildTree(newQueue);

    //Compress the file 
    string nString;
    newHT->huffCodes(newHT->getRoot(), nString);
    newHT->compressFile(transformedString, outputFile, objArr, objArrLen, filename);
}  
    




void codec::decoder(std::string filename, std::string outputFile){

    //Open input text file and dump its values into a stringstream
    std::string inputString;
    std::ifstream input(filename);

    if(input.is_open()){
        std::stringstream buffer;
        buffer << input.rdbuf();
        inputString = buffer.str();
        input.close();
    }

    //Decompress the file into the ibwtString variable
    huffTree * newHT = new huffTree();
    std::string ibwtString = newHT->decompressFile(inputString);

    //Call ibwt on the file data(which is the bwt data of the original compressed data)
    BWT transform;
    std::string ibwtDecoded;
    std::string ibwtDecodedString;
    std::stringstream ibwtStringStream(ibwtString);

    while(std::getline(ibwtStringStream, ibwtDecoded, '\n')){
       ibwtDecodedString += transform.ibwt(ibwtDecoded);
       ibwtDecodedString += '\n';
    }
    
    //Output file will be the name of the output file with .bwtHuff on the end of the name
    std::ofstream output(outputFile + ".bwtHuff");
    output << ibwtDecodedString;
    output.close();
}
