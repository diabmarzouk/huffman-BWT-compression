#include <iostream>
#include "huffNode.h"

using namespace std;

class huffObj {
    public:
        huffNode *node;

        // Overloaded parentheses
        bool operator()(huffObj const& d1, huffObj const&d2){
            return (d1.node->freq > d2.node->freq);
        }

        // Constructor
        huffObj();
};

// Default Constructor
huffObj::huffObj() : node(NULL){}

