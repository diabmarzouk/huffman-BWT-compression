#include <iostream>
#include <stdio.h>
#include <queue>
#include <string>
#include <locale>
#include <sstream>
#include <fstream>
#include <bitset>

#include "huffObj.h"
#include "bwt.h"

using namespace std;

// Comparator class used for STL's priority queue
class Compare {
        public:
                bool operator() (huffObj l, huffObj r){
                        return(l.node->freq > r.node->freq);
                }
};

// Huffman Tree class
class huffTree {

        private:
                huffNode *left, *right, *root;

        public:
                string prefCodes[256];

                huffTree();

                huffTree(huffNode * rt, priority_queue<huffObj, vector<huffObj>,Compare> pq);

                void buildTree(priority_queue<huffObj, vector<huffObj>,Compare> huffQ);

                void printQueue(priority_queue<huffObj, vector<huffObj>,Compare> huffQ);

                void compressFile(string oldString, string outFile, huffObj * objArr, int objArrLen, string inFile);

                string decompressFile(string inString);

                void huffCodes(huffNode * tree, string str);

                huffNode * getRoot();

};

// Default constructor
huffTree::huffTree() : left(NULL), right(NULL), root(NULL) {}


// Builds the tree by popping nodes from priority queue
void huffTree::buildTree(priority_queue<huffObj, vector<huffObj>,Compare> huffQ){
        while(huffQ.size()>1){
                left = huffQ.top().node ;
                huffQ.pop();

                right = huffQ.top().node ;
                huffQ.pop();

                huffNode *newRoot = new huffNode(0,left->freq+right->freq,left,right,NULL);
                root = newRoot;

                huffObj newObj;
                newObj.node = newRoot;
                huffQ.push(newObj);
        }
}


// Decompressor: Called when -d parameter is called in command line.
// It searches until our code word "BwtHuffmanEofTable " which is used to indicate
// the end of all the characters and frequencies pass-through.
// It then builds a new tree and converts the dump values to binary,
// which then is converted back to their original strings.
string huffTree::decompressFile(string inString){
    string binCodes;
    size_t eof, i = 0;
    char newChar;
    int nextElement, newFreq;
    size_t eoTable = inString.find("BwtHuffmanEofTable ");
    priority_queue<huffObj, vector<huffObj>,Compare> prioQ;
    while(i<eoTable){
        newChar = inString[i];
        stringstream(&inString[++i]) >> newFreq;
        huffNode * newNode = new huffNode(newChar,newFreq,NULL,NULL,NULL);
        huffObj newObj; newObj.node = newNode;
        prioQ.push(newObj);
        i = (inString.find(" ",i)!=-1) ? inString.find(" ",i)+1 : i+1;      //i++;
    }

    buildTree(prioQ);
    i = eoTable+17;
    eof = inString.size();

    while(i<eof){
        string bitString = bitset<8>(inString[i]).to_string();
        binCodes.append(bitString);
        i++;
    }

    int binSize = binCodes.size();
    huffNode * lastNode = root;
    string decodedString;
    for(int i = 0; i < binSize; i++){
        if(!lastNode->left && !lastNode->right){
            decodedString += lastNode->data;
            lastNode = root;
        }
        if(binCodes[i]=='0'){
            lastNode = lastNode->left;
        }else{
            lastNode = lastNode->right;
        }
    }
    return decodedString;
}

// Compressor: This function compresses a source file and creates the tree binary values as well as storing the 
// characters and frequencies before the "BwtHuffmanEofTable " keyword (which is used as a signal that this is the
// end of elements and frequencies)
void huffTree::compressFile(string oldString, string outFile, huffObj * objArr, int objArrLen, string inFile){
    int sSize = oldString.size();
    ofstream output (outFile);
    for(int i = 0; i < objArrLen; i++){
        output << objArr[i].node->data << objArr[i].node->freq << ' ';
    }
    output << "BwtHuffmanEofTable ";

    string prefixCode;
    int prefixSize, bitCount=7;
    bitset<8> newByte;
    for(int j = 0; j < sSize; j++){
        prefixCode = prefCodes[oldString[j]];
        prefixSize = prefixCode.size();
        for(int i=0; i < prefixSize; i++){
            if(bitCount==-1){
                unsigned long lo = newByte.to_ulong();
                unsigned char cha = static_cast<unsigned char>( lo );
                output << cha;
                bitCount=7;
            }
            newByte.set(bitCount,(int)(prefixCode[i]-'0'));
            bitCount--;
        }
    }

     for(int i = bitCount; i > -1; i--){
            newByte.set(i,0);
        }

     unsigned long lo = newByte.to_ulong();
     unsigned char cha = static_cast<unsigned char>( lo );
     output << cha;
     int inSize = oldString.size();
     int outSize = output.tellp();
     output.close();

     cout << inFile<<" -> " << inSize << " bytes" << endl << outFile << " -> " << outSize << " bytes" << endl;
     if(inSize < outSize){
        cout << "*** Size of compressed file > size of source file ***\n";
     }
}

// This function is used to convert a string to its tree equivalent binary
void huffTree::huffCodes(huffNode * tree, string str){
        if(!tree) return;

        if(tree->data != 0){
                prefCodes[tree->data] = str;
        }

        huffCodes(tree->left, str + "0");
        huffCodes(tree->right, str + "1");
}

// Get root. Its a getter.
huffNode * huffTree::getRoot(){
        return root;
}


