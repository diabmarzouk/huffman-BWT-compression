
#include <iostream>

using namespace std;

class huffNode {
        public:
                char data;
                int freq;
                huffNode *left, *right, *parent;
                //constructor
                huffNode();
                //parameterized constructor
                huffNode(char d, int f, huffNode *l, huffNode *r, huffNode *p);
};

// Default Constructor
huffNode::huffNode() : data(0), freq(0), left(NULL), right(NULL), parent(NULL){}

// Parameterized constructor
huffNode::huffNode(char d, int f, huffNode *l, huffNode *r, huffNode *p) : data(d), freq(f), left(l), right(r), parent(p){}

